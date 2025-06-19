# Yeep Language Specification

## Overview
Yeep is a simple, dynamically-typed interpreted programming language with C-like syntax. It supports variables, functions, control flow, and basic data types.

## Data Types

### Numbers
- Double-precision floating point numbers
- Examples: `42`, `3.14`, `-7.5`

### Strings
- UTF-8 encoded text enclosed in double quotes
- Examples: `"Hello"`, `"World!"`, `""`
- String concatenation with `+` operator

### Booleans
- `true` or `false`
- Used in conditional expressions

### Functions
- First-class values that can be assigned to variables
- Support closures and recursion

### Null
- Represents absence of value
- Default return value for functions without explicit return

## Variables

Variables are declared using the `let` keyword:

```yeep
let name = "John";
let age = 25;
let is_student = true;
```

Variables are dynamically typed and can be reassigned:

```yeep
let x = 42;
x = "now a string";
x = true;
```

## Operators

### Arithmetic
- `+` - Addition (also string concatenation)
- `-` - Subtraction
- `*` - Multiplication
- `/` - Division

### Comparison
- `==` - Equality
- `!=` - Inequality
- `<` - Less than
- `>` - Greater than
- `<=` - Less than or equal
- `>=` - Greater than or equal

### Logical
- `&&` - Logical AND
- `||` - Logical OR
- `!` - Logical NOT

### Assignment
- `=` - Assignment

## Control Flow

### If Statements
```yeep
if (condition) {
    // statements
} else {
    // statements
}
```

### While Loops
```yeep
while (condition) {
    // statements
}
```

## Functions

### Function Declaration
```yeep
fun function_name(param1, param2) {
    // statements
    return value; // optional
}
```

### Function Calls
```yeep
let result = function_name(arg1, arg2);
```

### Examples
```yeep
// Simple function
fun greet(name) {
    print("Hello, " + name + "!");
}

// Function with return value
fun add(a, b) {
    return a + b;
}

// Recursive function
fun factorial(n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}
```

## Built-in Functions

### print(expression)
Prints the value of an expression to standard output, followed by a newline.

```yeep
print("Hello, World!");
print(42);
print(true);
```

## Comments

Single-line comments start with `//`:

```yeep
// This is a comment
let x = 42; // This is also a comment
```

## Grammar

```
program        → statement* EOF ;

statement      → varDecl
               | funDecl
               | exprStmt
               | printStmt
               | returnStmt
               | ifStmt
               | whileStmt
               | block ;

varDecl        → "let" IDENTIFIER "=" expression ";" ;
funDecl        → "fun" IDENTIFIER "(" parameters? ")" block ;
exprStmt       → expression ";" ;
printStmt      → "print" "(" expression ")" ";" ;
returnStmt     → "return" expression? ";" ;
ifStmt         → "if" "(" expression ")" block ( "else" block )? ;
whileStmt      → "while" "(" expression ")" block ;
block          → "{" statement* "}" ;

expression     → assignment ;
assignment     → IDENTIFIER "=" assignment | logic_or ;
logic_or       → logic_and ( "||" logic_and )* ;
logic_and      → equality ( "&&" equality )* ;
equality       → comparison ( ( "!=" | "==" ) comparison )* ;
comparison     → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
term           → factor ( ( "-" | "+" ) factor )* ;
factor         → unary ( ( "/" | "*" ) unary )* ;
unary          → ( "!" | "-" ) unary | call ;
call           → primary ( "(" arguments? ")" )* ;
primary        → NUMBER | STRING | "true" | "false" | "null"
               | "(" expression ")" | IDENTIFIER ;

parameters     → IDENTIFIER ( "," IDENTIFIER )* ;
arguments      → expression ( "," expression )* ;
```

## Error Handling

The interpreter provides basic error messages for:
- Syntax errors during parsing
- Runtime errors (undefined variables, type mismatches, etc.)
- Division by zero
- Function call arity mismatches

## Shell Commands

When running in interactive mode, the following special commands are available:

- `help` - Display help information
- `exit` or `quit` - Exit the shell

## Examples

See the `examples/` directory for sample Yeep programs demonstrating various language features.
