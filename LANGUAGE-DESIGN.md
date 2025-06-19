# Yeep Language Design Document

## Language Philosophy

Yeep is designed to be a simple, readable, and practical programming language that combines the best aspects of modern programming languages while maintaining simplicity for beginners and power for experienced developers.

### Core Principles
1. **Simplicity First** - Easy to learn and understand
2. **Readable Syntax** - Code should read like natural language
3. **Type Safety** - Catch errors early when possible
4. **Performance** - Efficient execution with minimal overhead
5. **Extensibility** - Easy to add new features and libraries

## Language Features

### 1. Dynamic Typing with Optional Type Hints
```yeep
// Dynamic typing (current)
let age = 25;
let name = "Alice";

// Future: Optional type hints
let age: number = 25;
let name: string = "Alice";
```

### 2. First-Class Functions
```yeep
// Function assignment
let multiply = fun(a, b) {
    return a * b;
};

// Higher-order functions
fun apply_twice(func, value) {
    return func(func(value));
}

let double = fun(x) { return x * 2; };
print(apply_twice(double, 5)); // Output: 20
```

### 3. Lexical Scoping and Closures
```yeep
fun create_counter(initial) {
    let count = initial;
    
    return fun() {
        count = count + 1;
        return count;
    };
}

let counter = create_counter(0);
print(counter()); // 1
print(counter()); // 2
```

### 4. Built-in Data Structures

#### Arrays
```yeep
let fruits = ["apple", "banana", "cherry"];
fruits.push("date");
print(fruits.length); // 4
print(fruits[0]);      // "apple"

// Array methods
let numbers = [1, 2, 3, 4, 5];
let doubled = numbers.map(fun(x) { return x * 2; });
let sum = numbers.reduce(fun(acc, x) { return acc + x; }, 0);
```

#### Objects/Maps
```yeep
let person = {
    name: "Bob",
    age: 30,
    greet: fun() {
        print("Hello, I'm " + this.name);
    }
};

person.greet();
person.age = 31;
```

### 5. String Interpolation
```yeep
let name = "World";
let greeting = "Hello, ${name}!";
print(greeting); // "Hello, World!"

// Multi-line strings
let poem = """
    Roses are red,
    Violets are blue,
    Yeep is awesome,
    And so are you!
""";
```

### 6. Pattern Matching (Future)
```yeep
fun describe_number(n) {
    match n {
        case 0 => "zero";
        case 1 => "one";
        case 2..10 => "small number";
        case x if x < 0 => "negative";
        case _ => "large number";
    }
}
```

### 7. Error Handling
```yeep
// Current: Basic error messages
fun divide(a, b) {
    if (b == 0) {
        print("Error: Division by zero");
        return null;
    }
    return a / b;
}

// Future: Exception handling
fun divide(a, b) {
    if (b == 0) {
        throw Error("Division by zero");
    }
    return a / b;
}

try {
    let result = divide(10, 0);
} catch (error) {
    print("Caught error: " + error.message);
}
```

## Type System Design

### Current Type System
- **Dynamic typing** - Types determined at runtime
- **Type coercion** - Automatic conversion between compatible types
- **Duck typing** - "If it walks like a duck and quacks like a duck, it's a duck"

### Future Type System
- **Optional static typing** - Add type annotations for better tooling
- **Type inference** - Compiler infers types when not specified
- **Union types** - Variables can be one of several types
- **Generic types** - Reusable code with type parameters

```yeep
// Future type system examples
fun max<T>(a: T, b: T): T where T: Comparable {
    return a > b ? a : b;
}

let result: number | string = get_user_input();
```

## Memory Management

### Current Approach
- **Manual memory management** in C implementation
- **Reference counting** for objects
- **Garbage collection** planned for C++ version

### Future Improvements
- **Automatic memory management** with smart pointers
- **Generational garbage collection** for better performance
- **Memory pool allocation** for small objects

## Standard Library Design

### Core Modules
```yeep
// Math operations
import { sqrt, pow, sin, cos } from "std/math";

// String utilities
import { split, join, trim, replace } from "std/string";

// File I/O
import { read_file, write_file, exists } from "std/fs";

// HTTP client
import { get, post } from "std/http";

// JSON parsing
import { parse, stringify } from "std/json";
```

### Built-in Functions
```yeep
// Type checking
print(typeof(42));        // "number"
print(typeof("hello"));   // "string"

// Array operations
let arr = [1, 2, 3];
print(arr.length);        // 3
arr.push(4);
arr.pop();

// String operations
let str = "Hello World";
print(str.length);        // 11
print(str.upper());       // "HELLO WORLD"
print(str.split(" "));    // ["Hello", "World"]

// Object operations
let obj = { a: 1, b: 2 };
print(Object.keys(obj));   // ["a", "b"]
print(Object.values(obj)); // [1, 2]
```

## Concurrency Model (Future)

### Async/Await
```yeep
async fun fetch_data(url) {
    let response = await http.get(url);
    return response.json();
}

async fun main() {
    let data = await fetch_data("https://api.example.com/data");
    print(data);
}
```

### Channels and Goroutines
```yeep
fun worker(channel) {
    while (true) {
        let task = channel.receive();
        if (task == null) break;
        
        // Process task
        print("Processing: " + task);
    }
}

let ch = Channel.new();
go worker(ch);

ch.send("task1");
ch.send("task2");
ch.close();
```

## Error Handling Philosophy

### Current Approach
- **Return null or special values** for errors
- **Print error messages** to console
- **Early return** on error conditions

### Future Approach
- **Result types** for recoverable errors
- **Exceptions** for unrecoverable errors
- **Error propagation** with `?` operator

```yeep
// Future error handling
fun parse_number(str: string): Result<number, ParseError> {
    // Implementation
}

let result = parse_number("42")?;
print(result); // 42, or propagate error
```

## Performance Considerations

### Current Implementation
- **Tree-walking interpreter** - Simple but slow
- **C implementation** - Good performance for basic operations
- **Manual optimizations** - Hand-tuned critical paths

### Future Optimizations
- **Bytecode compiler** - Compile to intermediate representation
- **JIT compilation** - Dynamic optimization for hot code
- **Register-based VM** - More efficient than stack-based
- **Inline caching** - Speed up property access

## Development Tools

### Language Server Protocol (LSP)
- **Syntax highlighting** - Already implemented in VS Code extension
- **Code completion** - Intelligent suggestions
- **Error reporting** - Real-time error detection
- **Go to definition** - Navigate to function/variable definitions
- **Refactoring tools** - Rename, extract function, etc.

### Debugging Support
- **Source-level debugging** - Step through original code
- **Breakpoints** - Pause execution at specific lines
- **Variable inspection** - Examine variable values
- **Call stack** - See function call hierarchy

### Package Manager
```bash
# Future package manager commands
yeep init my-project
yeep add lodash
yeep remove unused-package
yeep publish
```

## Compatibility and Interoperability

### C/C++ Integration
```yeep
// Call C functions from Yeep
extern fun malloc(size: number): pointer;
extern fun free(ptr: pointer): void;

// Export Yeep functions to C
export fun fibonacci(n: number): number {
    // Implementation
}
```

### JavaScript Interop (Future)
```yeep
// Import JavaScript modules
import { moment } from "npm:moment";

// Use JavaScript APIs
let date = moment().format("YYYY-MM-DD");
```

## Security Model

### Current Security
- **Sandboxed execution** - Limited system access
- **Input validation** - Basic checks on user input
- **Memory safety** - Bounds checking for arrays

### Future Security
- **Capability-based security** - Explicit permissions for resources
- **Static analysis** - Detect security issues at compile time
- **Encrypted bytecode** - Protect intellectual property

## Testing Framework

```yeep
// Built-in testing support
test "addition works correctly" {
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
}

test "division by zero" {
    expect_error {
        divide(10, 0);
    };
}

// Run tests
yeep test
```

## Internationalization

```yeep
// Multi-language support
import { t } from "std/i18n";

print(t("hello_world")); // Uses current locale

// Number and date formatting
import { format_number, format_date } from "std/locale";

print(format_number(1234.56)); // Locale-specific formatting
print(format_date(Date.now())); // Locale-specific date
```

## Documentation Generation

```yeep
/**
 * Calculates the factorial of a number
 * @param n The number to calculate factorial for
 * @returns The factorial result
 * @example
 *   factorial(5) // Returns 120
 */
fun factorial(n: number): number {
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}
```

---

*This design document represents the current state and future vision for the Yeep programming language, emphasizing simplicity, performance, and developer experience.*
