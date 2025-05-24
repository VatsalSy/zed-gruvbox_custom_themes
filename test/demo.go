// Package main demonstrates Go syntax highlighting for Gruvbox Crisp Theme
package main

import (
	"context"
	"encoding/json"
	"fmt"
	"io"
	"log"
	"net/http"
	"sync"
	"time"
	
	"github.com/gorilla/mux"
	"github.com/pkg/errors"
)

// Constants and variables
const (
	// APIVersion represents the current API version
	APIVersion = "v2.0.0"
	// MaxRetries for network operations
	MaxRetries = 3
	// DefaultTimeout for requests
	DefaultTimeout = 30 * time.Second
)

var (
	// ErrNotFound is returned when a resource is not found
	ErrNotFound = errors.New("resource not found")
	// ErrInvalidInput indicates invalid input parameters
	ErrInvalidInput = errors.New("invalid input provided")
	
	logger = log.New(os.Stdout, "[APP] ", log.LstdFlags|log.Lshortfile)
)

// User represents a user in the system
type User struct {
	ID        int64     `json:"id" db:"id"`
	Username  string    `json:"username" db:"username"`
	Email     string    `json:"email" db:"email"`
	FullName  string    `json:"fullName,omitempty" db:"full_name"`
	Active    bool      `json:"active" db:"active"`
	CreatedAt time.Time `json:"createdAt" db:"created_at"`
	UpdatedAt time.Time `json:"updatedAt" db:"updated_at"`
}

// Validate checks if the user data is valid
func (u *User) Validate() error {
	if u.Username == "" {
		return fmt.Errorf("%w: username is required", ErrInvalidInput)
	}
	if u.Email == "" {
		return fmt.Errorf("%w: email is required", ErrInvalidInput)
	}
	// Email validation regex
	if !regexp.MustCompile(`^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$`).MatchString(u.Email) {
		return fmt.Errorf("%w: invalid email format", ErrInvalidInput)
	}
	return nil
}

// Repository defines the interface for data access
type Repository interface {
	FindByID(ctx context.Context, id int64) (*User, error)
	FindAll(ctx context.Context, limit, offset int) ([]*User, error)
	Create(ctx context.Context, user *User) error
	Update(ctx context.Context, user *User) error
	Delete(ctx context.Context, id int64) error
}

// Service provides business logic
type Service struct {
	repo   Repository
	cache  *Cache
	mu     sync.RWMutex
	config Config
}

// Config holds application configuration
type Config struct {
	DatabaseURL string        `json:"databaseUrl" env:"DATABASE_URL"`
	ServerPort  int           `json:"serverPort" env:"SERVER_PORT" default:"8080"`
	Debug       bool          `json:"debug" env:"DEBUG"`
	Timeout     time.Duration `json:"timeout" env:"TIMEOUT" default:"30s"`
}

// NewService creates a new service instance
func NewService(repo Repository, config Config) *Service {
	return &Service{
		repo:   repo,
		cache:  NewCache(1 * time.Hour),
		config: config,
	}
}

// GetUser retrieves a user by ID
func (s *Service) GetUser(ctx context.Context, id int64) (*User, error) {
	// Check cache first
	s.mu.RLock()
	if cached, ok := s.cache.Get(fmt.Sprintf("user:%d", id)); ok {
		s.mu.RUnlock()
		return cached.(*User), nil
	}
	s.mu.RUnlock()
	
	// Fetch from repository
	user, err := s.repo.FindByID(ctx, id)
	if err != nil {
		return nil, errors.Wrapf(err, "failed to find user %d", id)
	}
	
	if user == nil {
		return nil, ErrNotFound
	}
	
	// Update cache
	s.mu.Lock()
	s.cache.Set(fmt.Sprintf("user:%d", id), user)
	s.mu.Unlock()
	
	return user, nil
}

// CreateUser creates a new user
func (s *Service) CreateUser(ctx context.Context, user *User) error {
	// Validate input
	if err := user.Validate(); err != nil {
		return err
	}
	
	// Set timestamps
	now := time.Now()
	user.CreatedAt = now
	user.UpdatedAt = now
	
	// Create in repository
	if err := s.repo.Create(ctx, user); err != nil {
		return errors.Wrap(err, "failed to create user")
	}
	
	logger.Printf("Created user: %+v", user)
	return nil
}

// Handler handles HTTP requests
type Handler struct {
	service *Service
}

// NewHandler creates a new HTTP handler
func NewHandler(service *Service) *Handler {
	return &Handler{service: service}
}

// GetUserHandler handles GET /users/{id}
func (h *Handler) GetUserHandler(w http.ResponseWriter, r *http.Request) {
	vars := mux.Vars(r)
	id, err := strconv.ParseInt(vars["id"], 10, 64)
	if err != nil {
		respondWithError(w, http.StatusBadRequest, "Invalid user ID")
		return
	}
	
	ctx, cancel := context.WithTimeout(r.Context(), DefaultTimeout)
	defer cancel()
	
	user, err := h.service.GetUser(ctx, id)
	if err != nil {
		switch {
		case errors.Is(err, ErrNotFound):
			respondWithError(w, http.StatusNotFound, "User not found")
		default:
			respondWithError(w, http.StatusInternalServerError, "Internal server error")
		}
		return
	}
	
	respondWithJSON(w, http.StatusOK, user)
}

// Middleware for logging requests
func loggingMiddleware(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		start := time.Now()
		
		// Wrap response writer to capture status
		wrapped := &responseWriter{ResponseWriter: w, statusCode: http.StatusOK}
		
		// Call the next handler
		next.ServeHTTP(wrapped, r)
		
		// Log request details
		logger.Printf(
			"%s %s %d %v",
			r.Method,
			r.URL.Path,
			wrapped.statusCode,
			time.Since(start),
		)
	})
}

// Generic function with type constraints
func Filter[T any](slice []T, predicate func(T) bool) []T {
	result := make([]T, 0, len(slice))
	for _, item := range slice {
		if predicate(item) {
			result = append(result, item)
		}
	}
	return result
}

// Concurrent processing example
func ProcessUsers(users []*User) error {
	var wg sync.WaitGroup
	errCh := make(chan error, len(users))
	
	// Process users concurrently
	for _, user := range users {
		wg.Add(1)
		go func(u *User) {
			defer wg.Done()
			
			// Simulate processing
			time.Sleep(100 * time.Millisecond)
			
			if err := processUser(u); err != nil {
				errCh <- errors.Wrapf(err, "failed to process user %d", u.ID)
			}
		}(user)
	}
	
	// Wait for all goroutines to complete
	wg.Wait()
	close(errCh)
	
	// Collect errors
	var errs []error
	for err := range errCh {
		errs = append(errs, err)
	}
	
	if len(errs) > 0 {
		return errors.Errorf("processing failed with %d errors", len(errs))
	}
	
	return nil
}

// Interface with embedded interfaces
type Store interface {
	io.Closer
	Repository
	Ping(ctx context.Context) error
}

// Method with multiple return values
func parseConfig(data []byte) (config Config, err error) {
	err = json.Unmarshal(data, &config)
	if err != nil {
		return Config{}, errors.Wrap(err, "failed to parse config")
	}
	
	// Set defaults
	if config.ServerPort == 0 {
		config.ServerPort = 8080
	}
	if config.Timeout == 0 {
		config.Timeout = DefaultTimeout
	}
	
	return config, nil
}

// Defer, panic, and recover example
func safeExecute(fn func() error) (err error) {
	defer func() {
		if r := recover(); r != nil {
			err = fmt.Errorf("panic recovered: %v", r)
			logger.Printf("Recovered from panic: %v", r)
		}
	}()
	
	return fn()
}

// Channel usage
func worker(id int, jobs <-chan int, results chan<- int) {
	for job := range jobs {
		logger.Printf("Worker %d processing job %d", id, job)
		time.Sleep(time.Second)
		results <- job * 2
	}
}

// Select statement example
func multiplex(ctx context.Context, ch1, ch2 <-chan string) {
	for {
		select {
		case msg1 := <-ch1:
			fmt.Println("Received from ch1:", msg1)
		case msg2 := <-ch2:
			fmt.Println("Received from ch2:", msg2)
		case <-ctx.Done():
			fmt.Println("Context cancelled")
			return
		case <-time.After(5 * time.Second):
			fmt.Println("Timeout")
			return
		}
	}
}

// init function
func init() {
	// Initialize default configuration
	log.SetFlags(log.LstdFlags | log.Lshortfile)
}

// main function
func main() {
	// Parse command line flags
	var (
		port   = flag.Int("port", 8080, "Server port")
		dbURL  = flag.String("db", "postgres://localhost/myapp", "Database URL")
		debug  = flag.Bool("debug", false, "Enable debug mode")
	)
	flag.Parse()
	
	// Create configuration
	config := Config{
		DatabaseURL: *dbURL,
		ServerPort:  *port,
		Debug:       *debug,
		Timeout:     DefaultTimeout,
	}
	
	// Initialize repository and service
	repo := NewPostgresRepository(config.DatabaseURL)
	service := NewService(repo, config)
	handler := NewHandler(service)
	
	// Setup routes
	router := mux.NewRouter()
	router.Use(loggingMiddleware)
	
	// API routes
	api := router.PathPrefix("/api/v1").Subrouter()
	api.HandleFunc("/users/{id}", handler.GetUserHandler).Methods("GET")
	api.HandleFunc("/users", handler.CreateUserHandler).Methods("POST")
	api.HandleFunc("/users/{id}", handler.UpdateUserHandler).Methods("PUT")
	api.HandleFunc("/users/{id}", handler.DeleteUserHandler).Methods("DELETE")
	
	// Health check
	router.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
		respondWithJSON(w, http.StatusOK, map[string]string{
			"status": "healthy",
			"version": APIVersion,
		})
	})
	
	// Start server
	srv := &http.Server{
		Addr:         fmt.Sprintf(":%d", config.ServerPort),
		Handler:      router,
		ReadTimeout:  15 * time.Second,
		WriteTimeout: 15 * time.Second,
		IdleTimeout:  60 * time.Second,
	}
	
	logger.Printf("Starting server on port %d", config.ServerPort)
	if err := srv.ListenAndServe(); err != nil {
		logger.Fatalf("Server failed to start: %v", err)
	}
}