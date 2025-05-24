//! Rust Demo - Gruvbox Crisp Theme
//! Demonstrates Rust syntax highlighting features

use std::collections::{HashMap, HashSet};
use std::sync::{Arc, Mutex};
use std::error::Error;
use std::fmt::{self, Display};
use async_trait::async_trait;
use serde::{Serialize, Deserialize};

/// Constants and static variables
const MAX_BUFFER_SIZE: usize = 1024 * 1024; // 1MB
const API_VERSION: &str = "2.0.0";
static INSTANCE_COUNT: AtomicUsize = AtomicUsize::new(0);

/// Custom error type
#[derive(Debug, Clone)]
pub enum AppError {
    NotFound(String),
    InvalidInput { field: String, value: String },
    DatabaseError(String),
    NetworkError { code: u32, message: String },
}

impl Display for AppError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            AppError::NotFound(item) => write!(f, "Not found: {}", item),
            AppError::InvalidInput { field, value } => {
                write!(f, "Invalid input for {}: {}", field, value)
            }
            AppError::DatabaseError(msg) => write!(f, "Database error: {}", msg),
            AppError::NetworkError { code, message } => {
                write!(f, "Network error {}: {}", code, message)
            }
        }
    }
}

impl Error for AppError {}

/// Generic trait with associated types
pub trait Repository<T> {
    type Error;
    
    async fn find_by_id(&self, id: u64) -> Result<Option<T>, Self::Error>;
    async fn save(&mut self, entity: &T) -> Result<u64, Self::Error>;
    async fn delete(&mut self, id: u64) -> Result<bool, Self::Error>;
}

/// Struct with derive macros
#[derive(Debug, Clone, Serialize, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct User {
    pub id: u64,
    pub username: String,
    pub email: String,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub full_name: Option<String>,
    pub active: bool,
    #[serde(with = "chrono::serde::ts_seconds")]
    pub created_at: DateTime<Utc>,
}

/// Implementation block
impl User {
    /// Creates a new user
    pub fn new(username: String, email: String) -> Self {
        Self {
            id: 0,
            username,
            email,
            full_name: None,
            active: true,
            created_at: Utc::now(),
        }
    }
    
    /// Validates user data
    pub fn validate(&self) -> Result<(), AppError> {
        if self.username.is_empty() {
            return Err(AppError::InvalidInput {
                field: "username".to_string(),
                value: self.username.clone(),
            });
        }
        
        // Email regex pattern
        let email_regex = regex::Regex::new(r"^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$")
            .expect("Invalid regex");
            
        if !email_regex.is_match(&self.email) {
            return Err(AppError::InvalidInput {
                field: "email".to_string(),
                value: self.email.clone(),
            });
        }
        
        Ok(())
    }
}

/// Generic struct with lifetime parameters
#[derive(Debug)]
pub struct Cache<'a, T: Clone> {
    data: HashMap<String, T>,
    ttl: Duration,
    name: &'a str,
}

impl<'a, T: Clone> Cache<'a, T> {
    pub fn new(name: &'a str, ttl: Duration) -> Self {
        Self {
            data: HashMap::new(),
            ttl,
            name,
        }
    }
    
    pub fn get(&self, key: &str) -> Option<&T> {
        self.data.get(key)
    }
    
    pub fn insert(&mut self, key: String, value: T) -> Option<T> {
        self.data.insert(key, value)
    }
}

/// Enum with different variants
#[derive(Debug, Clone, Copy)]
pub enum Status {
    Pending,
    Processing { progress: f32 },
    Completed(DateTime<Utc>),
    Failed { error_code: u32, retry_count: u8 },
}

/// Async trait implementation
#[async_trait]
impl Repository<User> for UserRepository {
    type Error = AppError;
    
    async fn find_by_id(&self, id: u64) -> Result<Option<User>, Self::Error> {
        let users = self.users.lock().await;
        Ok(users.get(&id).cloned())
    }
    
    async fn save(&mut self, entity: &User) -> Result<u64, Self::Error> {
        entity.validate()?;
        
        let mut users = self.users.lock().await;
        let id = users.len() as u64 + 1;
        let mut user = entity.clone();
        user.id = id;
        users.insert(id, user);
        
        Ok(id)
    }
    
    async fn delete(&mut self, id: u64) -> Result<bool, Self::Error> {
        let mut users = self.users.lock().await;
        Ok(users.remove(&id).is_some())
    }
}

/// Pattern matching examples
pub fn process_status(status: Status) -> String {
    match status {
        Status::Pending => "Waiting to start".to_string(),
        Status::Processing { progress } => format!("Processing: {:.1}%", progress * 100.0),
        Status::Completed(time) => format!("Completed at {}", time.format("%Y-%m-%d %H:%M:%S")),
        Status::Failed { error_code, retry_count } => {
            format!("Failed with code {} (retries: {})", error_code, retry_count)
        }
    }
}

/// Macro definition
macro_rules! log_debug {
    ($($arg:tt)*) => {
        if cfg!(debug_assertions) {
            println!("[DEBUG] {}", format!($($arg)*));
        }
    };
}

/// Function with multiple generic parameters and where clause
pub fn merge_maps<K, V>(
    mut base: HashMap<K, V>,
    other: HashMap<K, V>,
) -> HashMap<K, V>
where
    K: Eq + Hash + Clone,
    V: Clone,
{
    for (key, value) in other {
        base.entry(key).or_insert(value);
    }
    base
}

/// Closure and iterator examples
pub fn process_numbers(numbers: Vec<i32>) -> Vec<i32> {
    numbers
        .into_iter()
        .filter(|&n| n > 0)
        .map(|n| n * 2)
        .filter_map(|n| {
            if n < 100 {
                Some(n)
            } else {
                None
            }
        })
        .collect()
}

/// Async function with error handling
pub async fn fetch_user_data(
    client: &reqwest::Client,
    user_id: u64,
) -> Result<User, Box<dyn Error>> {
    let url = format!("{}/users/{}", API_BASE_URL, user_id);
    
    let response = client
        .get(&url)
        .header("Authorization", "Bearer token")
        .timeout(Duration::from_secs(30))
        .send()
        .await?;
    
    if !response.status().is_success() {
        return Err(Box::new(AppError::NetworkError {
            code: response.status().as_u16() as u32,
            message: response.status().to_string(),
        }));
    }
    
    let user: User = response.json().await?;
    Ok(user)
}

/// Lifetime elision and references
impl<'a> Display for Cache<'a, String> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Cache '{}' with {} items", self.name, self.data.len())
    }
}

/// Unsafe code block
pub fn read_raw_bytes(ptr: *const u8, len: usize) -> Vec<u8> {
    unsafe {
        assert!(!ptr.is_null());
        std::slice::from_raw_parts(ptr, len).to_vec()
    }
}

/// Module with visibility modifiers
mod internal {
    pub(crate) fn helper_function() -> u32 {
        42
    }
    
    pub(super) struct InternalData {
        value: String,
    }
}

/// Tests module
#[cfg(test)]
mod tests {
    use super::*;
    
    #[test]
    fn test_user_validation() {
        let user = User::new("john_doe".to_string(), "john@example.com".to_string());
        assert!(user.validate().is_ok());
        
        let invalid_user = User::new("".to_string(), "invalid-email".to_string());
        assert!(invalid_user.validate().is_err());
    }
    
    #[tokio::test]
    async fn test_async_function() {
        let result = async_operation().await;
        assert_eq!(result, 42);
    }
}

/// Main function
#[tokio::main]
async fn main() -> Result<(), Box<dyn Error>> {
    // Initialize logging
    env_logger::init();
    log_debug!("Starting application");
    
    // Create user repository
    let repo = Arc::new(Mutex::new(UserRepository::new()));
    
    // Create and save user
    let user = User::new("alice".to_string(), "alice@example.com".to_string());
    let user_id = repo.lock().await.save(&user).await?;
    
    println!("Created user with ID: {}", user_id);
    
    // Pattern matching with if let
    if let Some(found_user) = repo.lock().await.find_by_id(user_id).await? {
        println!("Found user: {:?}", found_user);
    }
    
    // Using ? operator for error propagation
    let status = get_processing_status().await?;
    println!("Status: {}", process_status(status));
    
    Ok(())
}