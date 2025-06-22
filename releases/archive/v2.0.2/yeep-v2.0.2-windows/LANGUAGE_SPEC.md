# Yeep Language Specification v2.0
## A Simple, Powerful Programming Language

### Design Goals
- Simple, readable syntax
- Rich built-in function library
- Easy to parse and implement
- Support for modern programming concepts

### Grammar Specification

```
program         → statement* EOF

statement       → exprStmt
                | printStmt
                | letStmt
                | blockStmt
                | ifStmt
                | whileStmt
                | forStmt
                | returnStmt
                | functionStmt

exprStmt        → expression ";"
printStmt       → "print" expression ";"
letStmt         → "let" IDENTIFIER ("=" expression)? ";"
blockStmt       → "{" statement* "}"
ifStmt          → "if" "(" expression ")" statement ("else" statement)?
whileStmt       → "while" "(" expression ")" statement
forStmt         → "for" "(" (letStmt | exprStmt | ";") expression? ";" expression? ")" statement
returnStmt      → "return" expression? ";"
functionStmt    → "fun" IDENTIFIER "(" parameters? ")" blockStmt

parameters      → IDENTIFIER ("," IDENTIFIER)*
arguments       → expression ("," expression)*

expression      → assignment
assignment      → IDENTIFIER "=" assignment | logicalOr
logicalOr       → logicalAnd ("||" logicalAnd)*
logicalAnd      → equality ("&&" equality)*
equality        → comparison (("==" | "!=") comparison)*
comparison      → term ((">" | ">=" | "<" | "<=") term)*
term            → factor (("+" | "-") factor)*
factor          → unary (("*" | "/" | "%") unary)*
unary           → ("!" | "-") unary | call
call            → primary ("(" arguments? ")")*
primary         → NUMBER | STRING | "true" | "false" | "nil"
                | "(" expression ")" | IDENTIFIER

NUMBER          → DIGIT+ ("." DIGIT+)?
STRING          → "\"" <any char except "\">* "\""
IDENTIFIER      → ALPHA (ALPHA | DIGIT)*
ALPHA           → "a" ... "z" | "A" ... "Z" | "_"
DIGIT           → "0" ... "9"
```

### Data Types

1. **Number**: Double-precision floating point
   - Examples: `42`, `3.14`, `-7.5`

2. **String**: UTF-8 text in double quotes
   - Examples: `"Hello"`, `"World"`, `""`

3. **Boolean**: `true` or `false`

4. **Nil**: Represents absence of value

5. **Function**: First-class functions

### Built-in Functions

#### Mathematical Functions
- `abs(x)` - Absolute value
- `sqrt(x)` - Square root
- `pow(x, y)` - x raised to power y
- `max(x, y, ...)` - Maximum value
- `min(x, y, ...)` - Minimum value
- `floor(x)` - Floor value
- `ceil(x)` - Ceiling value
- `round(x)` - Round to nearest integer
- `sin(x)`, `cos(x)`, `tan(x)` - Trigonometric functions
- `log(x)` - Natural logarithm
- `random()` - Random number 0-1

#### String Functions
- `length(str)` or `len(str)` - String length
- `substring(str, start, end)` or `substr(str, start, end)` - Extract substring
- `uppercase(str)` or `upper(str)` - Convert to uppercase
- `lowercase(str)` or `lower(str)` - Convert to lowercase
- `contains(str, substr)` - Check if string contains substring
- `startsWith(str, prefix)` - Check if string starts with prefix
- `endsWith(str, suffix)` - Check if string ends with suffix
- `replace(str, old, new)` - Replace occurrences
- `split(str, delimiter)` - Split string into array
- `trim(str)` - Remove leading/trailing whitespace

#### Type Functions
- `type(value)` - Get type name
- `toString(value)` or `str(value)` - Convert to string
- `toNumber(value)` or `num(value)` - Convert to number
- `toBoolean(value)` or `bool(value)` - Convert to boolean

#### I/O Functions
- `print(value)` - Print to console
- `input(prompt?)` - Read user input
- `readFile(filename)` - Read file contents
- `writeFile(filename, content)` - Write to file

#### Utility Functions
- `time()` - Current timestamp
- `sleep(seconds)` - Pause execution
- `exit(code?)` - Exit program

### Language Features

#### Variables
```yeep
let name = "John";
let age = 25;
let isStudent = true;
```

#### Functions
```yeep
fun greet(name) {
    print("Hello, " + name + "!");
}

fun add(a, b) {
    return a + b;
}
```

#### Control Flow
```yeep
if (age >= 18) {
    print("Adult");
} else {
    print("Minor");
}

while (count < 10) {
    count = count + 1;
}

for (let i = 0; i < 10; i = i + 1) {
    print(i);
}
```

#### String Operations
```yeep
let message = "Hello " + "World";
let result = "Answer: " + toString(42);
```

### Example Programs

#### Calculator
```yeep
fun calculator() {
    print("Simple Calculator");
    let a = toNumber(input("Enter first number: "));
    let b = toNumber(input("Enter second number: "));
    
    print("Sum: " + (a + b));
    print("Difference: " + (a - b));
    print("Product: " + (a * b));
    print("Quotient: " + (a / b));
    print("Power: " + pow(a, b));
    print("Max: " + max(a, b));
    print("Min: " + min(a, b));
}

calculator();
```

#### String Processing
```yeep
fun processText(text) {
    print("Original: " + text);
    print("Length: " + length(text));
    print("Uppercase: " + uppercase(text));
    print("Lowercase: " + lowercase(text));
    
    if (contains(text, "hello")) {
        print("Contains 'hello'");
    }
    
    if (startsWith(text, "Hello")) {
        print("Starts with 'Hello'");
    }
}

processText("Hello World");
```

### Error Handling
- Runtime errors stop execution with descriptive messages
- Type errors are caught at runtime
- Undefined variables/functions throw errors

### Comments
```yeep
// Single line comment
/* Multi-line
   comment */
```

This specification provides a clean, simple language that's easy to implement and use!
