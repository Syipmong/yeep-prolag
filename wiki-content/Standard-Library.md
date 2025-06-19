# Standard Library

This page documents the built-in functions and features available in the Yeep programming language.

## Overview

The Yeep standard library provides essential functionality for common programming tasks. As Yeep is in active development, the standard library is continuously expanding with new features and improvements.

## Core Functions

### Output Functions

#### `print`
Outputs values to the console.

**Syntax:**
```yeep
print expression
print "Hello, World!"
print variable_name
print 42
```

**Examples:**
```yeep
print "Welcome to Yeep!"
name = "Alice"
print name
print "Hello, " + name

number = 123
print number
print "The answer is: " + number
```

**Behavior:**
- Automatically converts values to string representation
- Adds a newline after each output
- Supports string concatenation with `+` operator

### Arithmetic Functions

#### Basic Operators
Standard mathematical operations are built into the language.

**Addition (`+`)**
```yeep
result = 5 + 3        # Result: 8
total = a + b + c     # Sum of variables
```

**Subtraction (`-`)**
```yeep
difference = 10 - 4   # Result: 6
remaining = total - used
```

**Multiplication (`*`)**
```yeep
product = 6 * 7       # Result: 42
area = width * height
```

**Division (`/`)**
```yeep
quotient = 15 / 3     # Result: 5
average = sum / count
```

**Modulo (`%`)**
```yeep
remainder = 17 % 5    # Result: 2
is_even = number % 2  # 0 if even, 1 if odd
```

### Logical Functions

#### Boolean Operators

**AND (`and`)**
```yeep
result = true and false   # Result: false
valid = age >= 18 and has_license
```

**OR (`or`)**
```yeep
result = true or false    # Result: true
eligible = is_student or is_senior
```

**NOT (`not`)**
```yeep
result = not true         # Result: false
invalid = not is_valid
```

#### Comparison Operators

**Equality (`==`)**
```yeep
is_equal = 5 == 5         # Result: true
match = name == "Alice"
```

**Inequality (`!=`)**
```yeep
different = 5 != 3        # Result: true
changed = old_value != new_value
```

**Greater Than (`>`)**
```yeep
bigger = 10 > 5           # Result: true
passing = score > 60
```

**Less Than (`<`)**
```yeep
smaller = 3 < 8           # Result: true
under_limit = count < max_count
```

**Greater Than or Equal (`>=`)**
```yeep
at_least = 5 >= 5         # Result: true
qualified = experience >= required_years
```

**Less Than or Equal (`<=`)**
```yeep
at_most = 3 <= 7          # Result: true
within_budget = cost <= budget
```

## Data Types

### Primitive Types

#### Numbers
- **Integers**: Whole numbers (32-bit signed)
- **Floats**: Decimal numbers (double precision)

```yeep
# Integer examples
age = 25
count = 0
negative = -42

# Float examples (planned)
price = 19.99
pi = 3.14159
temperature = -5.5
```

#### Strings
- **String Literals**: Text enclosed in double quotes
- **Concatenation**: Joining strings with `+` operator

```yeep
# String examples
name = "Alice"
greeting = "Hello, World!"
empty = ""

# Concatenation
full_name = first_name + " " + last_name
message = "Hello, " + name + "!"
```

#### Booleans
- **true**: Boolean true value
- **false**: Boolean false value

```yeep
# Boolean examples
is_valid = true
is_complete = false
result = 5 > 3  # Evaluates to true
```

### Variables

#### Variable Assignment
```yeep
# Simple assignment
name = "Alice"
age = 30
is_student = true

# Expression assignment
total = price * quantity
full_name = first_name + " " + last_name
is_adult = age >= 18
```

#### Variable Scope
- **Global Variables**: Accessible throughout the program
- **Local Variables**: Limited to current block (planned feature)

## Built-in Constants

### Mathematical Constants (Planned)
```yeep
# Future mathematical constants
PI = 3.14159265359
E = 2.71828182846
```

### System Constants (Planned)
```yeep
# Future system constants
VERSION = "1.0.8"
PLATFORM = "Windows"  # or "Linux", "macOS"
```

## String Operations

### Current Support
```yeep
# String concatenation
greeting = "Hello, " + name + "!"
path = directory + "/" + filename

# String with numbers
message = "Count: " + count
```

### Planned Features
```yeep
# String manipulation (future)
length = len(text)          # String length
upper = uppercase(text)     # Convert to uppercase
lower = lowercase(text)     # Convert to lowercase
substr = substring(text, 0, 5)  # Extract substring
```

## Mathematical Functions (Planned)

### Basic Math
```yeep
# Planned mathematical functions
absolute = abs(-5)          # Absolute value
power = pow(2, 3)           # 2 to the power of 3
square_root = sqrt(16)      # Square root
```

### Advanced Math
```yeep
# Planned advanced functions
sine = sin(angle)           # Trigonometric sine
cosine = cos(angle)         # Trigonometric cosine
log = log(number)           # Natural logarithm
log10 = log10(number)       # Base-10 logarithm
```

## Input/Output Functions (Planned)

### User Input
```yeep
# Planned input functions
name = input("Enter your name: ")
age = input_number("Enter your age: ")
confirmed = input_boolean("Continue? (y/n): ")
```

### File Operations
```yeep
# Planned file functions
content = read_file("data.txt")
write_file("output.txt", content)
append_file("log.txt", message)
exists = file_exists("config.txt")
```

## Utility Functions (Planned)

### Type Checking
```yeep
# Planned type checking functions
is_num = is_number(value)
is_str = is_string(value)
is_bool = is_boolean(value)
type_name = type_of(value)
```

### Conversion Functions
```yeep
# Planned conversion functions
number = to_number("123")
text = to_string(456)
flag = to_boolean("true")
```

## Collection Functions (Future)

### Arrays
```yeep
# Future array support
numbers = [1, 2, 3, 4, 5]
names = ["Alice", "Bob", "Charlie"]
length = len(numbers)
first = numbers[0]
```

### Array Operations
```yeep
# Future array operations
append(numbers, 6)          # Add element
remove(numbers, 2)          # Remove element
sorted = sort(numbers)      # Sort array
reversed = reverse(numbers) # Reverse array
```

## Error Handling (Future)

### Try-Catch
```yeep
# Future error handling
try {
    result = risky_operation()
} catch (error) {
    print "Error occurred: " + error
}
```

### Assertions
```yeep
# Future assertion support
assert(age >= 0, "Age cannot be negative")
assert(name != "", "Name cannot be empty")
```

## Standard Library Modules (Future)

### Math Module
```yeep
# Future module system
import math
result = math.sin(angle)
pi_value = math.PI
```

### String Module
```yeep
import string
cleaned = string.trim(text)
replaced = string.replace(text, "old", "new")
```

### File Module
```yeep
import file
content = file.read("data.txt")
file.write("output.txt", content)
```

### System Module
```yeep
import system
current_time = system.time()
platform = system.platform()
user = system.user()
```

## Documentation Conventions

### Function Signatures
When documenting functions, we use this format:
```
function_name(parameter1, parameter2, ...) -> return_type
```

### Parameter Types
- `string`: Text value
- `number`: Integer or float
- `boolean`: True or false value
- `any`: Any type accepted

### Return Values
- Functions return values that can be assigned to variables
- Some functions perform actions without returning values
- Error conditions may return special error values

## Contributing to the Standard Library

### Guidelines
- Keep functions simple and focused
- Follow consistent naming conventions
- Provide comprehensive examples
- Ensure cross-platform compatibility

### Proposing New Functions
1. Open a GitHub issue with the proposal
2. Include use cases and examples
3. Discuss implementation details
4. Submit a pull request with implementation

---

The Yeep standard library is continuously evolving. Check the [GitHub repository](https://github.com/itsthatblackhat/yeep-prolag) for the latest updates and feature additions. For language specification details, see the [Language Reference](Language-Reference).
