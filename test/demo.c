/**
 * C Demo - Gruvbox Crisp Theme
 * Demonstrates various C language syntax highlighting features
 * Author: Vatsal Sanjay
 * Date: 2024-01-20
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <errno.h>
#include <time.h>

// Preprocessor directives
#define VERSION "1.0.0"
#define MAX_BUFFER_SIZE 1024
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#ifdef DEBUG
    #define DEBUG_PRINT(fmt, ...) \
        fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt "\n", \
                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
#else
    #define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

// Conditional compilation
#if defined(__linux__)
    #define PLATFORM "Linux"
#elif defined(__APPLE__)
    #define PLATFORM "macOS"
#elif defined(_WIN32)
    #define PLATFORM "Windows"
#else
    #define PLATFORM "Unknown"
#endif

// Type definitions
typedef unsigned char byte;
typedef struct node Node;
typedef enum { FALSE = 0, TRUE = 1 } Boolean;

// Enumerations
enum Status {
    STATUS_OK = 0,
    STATUS_ERROR = -1,
    STATUS_INVALID_PARAM = -2,
    STATUS_OUT_OF_MEMORY = -3,
    STATUS_FILE_NOT_FOUND = -4
};

enum ColorIndex {
    COLOR_BLACK,
    COLOR_RED,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
    COLOR_MAGENTA,
    COLOR_CYAN,
    COLOR_WHITE,
    COLOR_COUNT
};

// Structure definitions
struct Point {
    double x;
    double y;
    double z;
};

typedef struct {
    char name[64];
    int age;
    float salary;
    struct {
        char street[128];
        char city[64];
        char zip[16];
    } address;
} Person;

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

// Union example
union Data {
    int i;
    float f;
    char str[20];
    struct {
        unsigned char r, g, b, a;
    } color;
};

// Bit fields
typedef struct {
    unsigned int enabled : 1;
    unsigned int mode : 3;
    unsigned int priority : 4;
    unsigned int reserved : 24;
} Config;

// Function prototypes
static void print_banner(const char *text);
int calculate_factorial(int n);
void swap(int *a, int *b);
char* string_reverse(char *str);
Node* create_node(int data);
void process_array(int arr[], size_t size);
double calculate_distance(struct Point *p1, struct Point *p2);
void demonstrate_pointers(void);
void file_operations_demo(void);
void dynamic_memory_demo(void);
void bit_manipulation_demo(void);
void* generic_function(void *data, size_t size, int (*compare)(const void*, const void*));

// Global variables
static const char *COLORS[] = {
    "\033[0;30m", "\033[0;31m", "\033[0;32m", "\033[0;33m",
    "\033[0;34m", "\033[0;35m", "\033[0;36m", "\033[0;37m"
};
static const char *RESET = "\033[0m";

volatile int interrupt_flag = 0;
extern int external_variable;

// Static function implementation
static void print_banner(const char *text) {
    int len = strlen(text);
    printf("\n");
    for (int i = 0; i < len + 4; i++) printf("*");
    printf("\n* %s *\n", text);
    for (int i = 0; i < len + 4; i++) printf("*");
    printf("\n\n");
}

// Recursive function
int calculate_factorial(int n) {
    if (n < 0) {
        errno = EINVAL;
        return -1;
    }
    return (n <= 1) ? 1 : n * calculate_factorial(n - 1);
}

// Pointer manipulation
void swap(int *a, int *b) {
    if (a == NULL || b == NULL) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

// String manipulation
char* string_reverse(char *str) {
    if (!str || !*str) return str;
    
    char *start = str;
    char *end = str + strlen(str) - 1;
    
    while (start < end) {
        char temp = *start;
        *start++ = *end;
        *end-- = temp;
    }
    
    return str;
}

// Dynamic memory allocation
Node* create_node(int data) {
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("malloc failed");
        return NULL;
    }
    
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}

// Array processing
void process_array(int arr[], size_t size) {
    printf("Array contents: ");
    for (size_t i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i < size - 1) printf(", ");
    }
    printf("\n");
    
    // Find min and max
    int min = INT_MAX, max = INT_MIN;
    long long sum = 0;
    
    for (size_t i = 0; i < size; i++) {
        min = MIN(min, arr[i]);
        max = MAX(max, arr[i]);
        sum += arr[i];
    }
    
    printf("Min: %d, Max: %d, Average: %.2f\n", 
           min, max, (double)sum / size);
}

// Mathematical calculations
double calculate_distance(struct Point *p1, struct Point *p2) {
    if (!p1 || !p2) return -1.0;
    
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    double dz = p2->z - p1->z;
    
    return sqrt(dx*dx + dy*dy + dz*dz);
}

// Pointer arithmetic and arrays
void demonstrate_pointers(void) {
    print_banner("Pointer Demonstration");
    
    int numbers[] = {10, 20, 30, 40, 50};
    int *ptr = numbers;
    
    printf("Array address: %p\n", (void*)numbers);
    printf("Pointer value: %p\n", (void*)ptr);
    
    // Different ways to access array elements
    for (int i = 0; i < ARRAY_SIZE(numbers); i++) {
        printf("numbers[%d] = %d, *(ptr+%d) = %d, ptr[%d] = %d\n",
               i, numbers[i], i, *(ptr+i), i, ptr[i]);
    }
    
    // Pointer to pointer
    int **ptr_ptr = &ptr;
    printf("\nPointer to pointer: %p -> %p -> %d\n", 
           (void*)ptr_ptr, (void*)*ptr_ptr, **ptr_ptr);
    
    // Function pointers
    int (*math_func)(int) = calculate_factorial;
    printf("\nFactorial of 5: %d\n", math_func(5));
}

// File I/O operations
void file_operations_demo(void) {
    print_banner("File Operations");
    
    const char *filename = "test_gruvbox.txt";
    FILE *file = fopen(filename, "w+");
    
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    // Writing to file
    fprintf(file, "Gruvbox Crisp Theme Demo\n");
    fprintf(file, "Version: %s\n", VERSION);
    fprintf(file, "Platform: %s\n", PLATFORM);
    
    // Writing binary data
    int data[] = {0xFF, 0x00, 0xAB, 0xCD};
    fwrite(data, sizeof(int), ARRAY_SIZE(data), file);
    
    // Seek and read
    rewind(file);
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("Read: %s", buffer);
    }
    
    fclose(file);
    remove(filename);
}

// Dynamic memory management
void dynamic_memory_demo(void) {
    print_banner("Dynamic Memory Demo");
    
    // Allocate memory for array
    size_t count = 10;
    int *dynamic_array = (int*)calloc(count, sizeof(int));
    
    if (dynamic_array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    
    // Initialize array
    for (size_t i = 0; i < count; i++) {
        dynamic_array[i] = rand() % 100;
    }
    
    process_array(dynamic_array, count);
    
    // Resize array
    count *= 2;
    int *temp = (int*)realloc(dynamic_array, count * sizeof(int));
    if (temp != NULL) {
        dynamic_array = temp;
        printf("Array resized to %zu elements\n", count);
    }
    
    // Clean up
    free(dynamic_array);
    dynamic_array = NULL;
}

// Bit manipulation
void bit_manipulation_demo(void) {
    print_banner("Bit Manipulation");
    
    unsigned int flags = 0;
    
    // Set bits
    flags |= (1 << 0);  // Set bit 0
    flags |= (1 << 3);  // Set bit 3
    flags |= (1 << 7);  // Set bit 7
    
    printf("Flags: 0x%08X (binary: ", flags);
    for (int i = 31; i >= 0; i--) {
        printf("%d", (flags >> i) & 1);
        if (i % 8 == 0 && i > 0) printf(" ");
    }
    printf(")\n");
    
    // Check if bit is set
    int bit_pos = 3;
    if (flags & (1 << bit_pos)) {
        printf("Bit %d is set\n", bit_pos);
    }
    
    // Clear bit
    flags &= ~(1 << bit_pos);
    printf("After clearing bit %d: 0x%08X\n", bit_pos, flags);
    
    // Toggle bit
    flags ^= (1 << 5);
    printf("After toggling bit 5: 0x%08X\n", flags);
    
    // Count set bits
    unsigned int temp = flags;
    int count = 0;
    while (temp) {
        count += temp & 1;
        temp >>= 1;
    }
    printf("Number of set bits: %d\n", count);
}

// Variadic function
double average(int count, ...) {
    va_list args;
    va_start(args, count);
    
    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        sum += va_arg(args, double);
    }
    
    va_end(args);
    return count > 0 ? sum / count : 0.0;
}

// Complex macro with multiple statements
#define SAFE_FREE(ptr) do { \
    if ((ptr) != NULL) { \
        free(ptr); \
        (ptr) = NULL; \
    } \
} while(0)

// Inline function (C99)
static inline int square(int x) {
    return x * x;
}

// Main function
int main(int argc, char *argv[]) {
    printf("%sGruvbox Crisp Theme - C Language Demo%s\n", COLORS[COLOR_GREEN], RESET);
    printf("Version: %s, Platform: %s\n\n", VERSION, PLATFORM);
    
    // Command line arguments
    if (argc > 1) {
        printf("Command line arguments:\n");
        for (int i = 1; i < argc; i++) {
            printf("  argv[%d]: %s\n", i, argv[i]);
        }
        printf("\n");
    }
    
    // Initialize random seed
    srand(time(NULL));
    
    // Demonstrate various features
    demonstrate_pointers();
    dynamic_memory_demo();
    bit_manipulation_demo();
    file_operations_demo();
    
    // Structure usage
    Person person = {
        .name = "John Doe",
        .age = 30,
        .salary = 75000.50,
        .address = {
            .street = "123 Main St",
            .city = "Anytown",
            .zip = "12345"
        }
    };
    
    printf("\nPerson Info:\n");
    printf("  Name: %s\n", person.name);
    printf("  Age: %d\n", person.age);
    printf("  Salary: $%.2f\n", person.salary);
    printf("  Address: %s, %s %s\n", 
           person.address.street, person.address.city, person.address.zip);
    
    // Union usage
    union Data data;
    data.i = 1234;
    printf("\nUnion as int: %d\n", data.i);
    data.f = 3.14159f;
    printf("Union as float: %f\n", data.f);
    data.color = (typeof(data.color)){255, 128, 64, 255};
    printf("Union as color: RGBA(%d, %d, %d, %d)\n", 
           data.color.r, data.color.g, data.color.b, data.color.a);
    
    // Switch statement
    enum Status status = STATUS_OK;
    switch (status) {
        case STATUS_OK:
            printf("\nOperation completed successfully\n");
            break;
        case STATUS_ERROR:
            fprintf(stderr, "An error occurred\n");
            break;
        case STATUS_INVALID_PARAM:
            fprintf(stderr, "Invalid parameter\n");
            break;
        default:
            fprintf(stderr, "Unknown status: %d\n", status);
    }
    
    // Ternary operator
    int x = 42, y = 17;
    int max_val = (x > y) ? x : y;
    printf("\nMaximum of %d and %d is %d\n", x, y, max_val);
    
    // Goto example (use sparingly!)
    int counter = 0;
retry:
    if (++counter < 3) {
        DEBUG_PRINT("Attempt %d", counter);
        goto retry;
    }
    
    printf("\n%sProgram completed successfully!%s\n", COLORS[COLOR_CYAN], RESET);
    return EXIT_SUCCESS;
}