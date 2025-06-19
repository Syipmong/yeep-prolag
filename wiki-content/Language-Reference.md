# Yeep Language Reference 📖

Complete syntax and feature reference for the Yeep programming language.

---

## 📋 Table of Contents

- [**Lexical Structure**](#-lexical-structure)
- [**Data Types**](#-data-types)
- [**Variables**](#-variables)
- [**Operators**](#-operators)
- [**Control Flow**](#-control-flow)
- [**Functions**](#-functions)
- [**Built-in Functions**](#-built-in-functions)
- [**Comments**](#-comments)
- [**Grammar**](#-grammar)

---

## 🔤 Lexical Structure

### Keywords
```
let       - Variable declaration
if        - Conditional statement
else      - Alternative branch
while     - Loop statement
fun       - Function declaration
return    - Return from function
true      - Boolean literal
false     - Boolean literal
print     - Built-in print function
```

### Identifiers
- Start with letter (a-z, A-Z) or underscore (_)
- Followed by letters, digits (0-9), or underscores
- Case-sensitive

**Valid identifiers:**
```yeep
name
userName
_private
count1
MAX_VALUE
```

**Invalid identifiers:**
```yeep
1name     // Cannot start with digit
let       // Keyword
user-name // Hyphen not allowed
```

### Literals

#### Number Literals
```yeep
42        // Integer
3.14159   // Decimal
-10       // Negative
0         // Zero
```

#### String Literals
```yeep
"Hello"           // Basic string
"Hello, World!"   // String with punctuation
""                // Empty string
"Line 1\nLine 2"  // String with newline
```

#### Boolean Literals
```yeep
true              // Boolean true
false             // Boolean false
```

---

## 📊 Data Types

### Number
- Represents both integers and floating-point numbers
- Double-precision floating point internally

```yeep
let integer = 42;
let decimal = 3.14159;
let negative = -100;
```

### String
- Sequence of characters enclosed in double quotes
- Supports concatenation with any data type

```yeep
let name = "Alice";
let message = "Hello, " + name;
```

### Boolean
- Logical values: `true` or `false`
- Used in conditional expressions

```yeep
let isValid = true;
let isComplete = false;
```

---

## 📝 Variables

### Declaration
```yeep
let variableName = expression;
```

### Assignment
```yeep
variableName = newValue;
```

### Examples
```yeep
let x = 10;           // Declaration with initialization
x = 20;               // Assignment

let name = "Alice";   // String variable
let isActive = true;  // Boolean variable
```

### Scope Rules
- Variables are scoped to the block where they're declared
- Function parameters create new local variables
- Inner scopes can access outer scope variables

```yeep
let global = "I'm global";

fun example() {
    let local = "I'm local";
    print(global);  // OK - can access global
    print(local);   // OK - can access local
}

// print(local);  // ERROR - local not accessible here
```

---

## ⚡ Operators

### Arithmetic Operators

| Operator | Description | Example | Result |
|----------|-------------|---------|---------|
| `+` | Addition | `5 + 3` | `8` |
| `-` | Subtraction | `5 - 3` | `2` |
| `*` | Multiplication | `5 * 3` | `15` |
| `/` | Division | `6 / 3` | `2` |
| `%` | Modulo | `5 % 3` | `2` |

```yeep
let a = 10;
let b = 3;
print(a + b);  // 13
print(a - b);  // 7
print(a * b);  // 30
print(a / b);  // 3
print(a % b);  // 1
```

### Comparison Operators

| Operator | Description | Example | Result |
|----------|-------------|---------|---------|
| `==` | Equal | `5 == 5` | `true` |
| `!=` | Not equal | `5 != 3` | `true` |
| `<` | Less than | `3 < 5` | `true` |
| `>` | Greater than | `5 > 3` | `true` |
| `<=` | Less than or equal | `3 <= 5` | `true` |
| `>=` | Greater than or equal | `5 >= 5` | `true` |

```yeep
let x = 5;
let y = 10;
print(x == y);  // false
print(x != y);  // true
print(x < y);   // true
print(x <= y);  // true
```

### Logical Operators

| Operator | Description | Example | Result |
|----------|-------------|---------|---------|
| `&&` | Logical AND | `true && false` | `false` |
| `\|\|` | Logical OR | `true \|\| false` | `true` |
| `!` | Logical NOT | `!true` | `false` |

```yeep
let a = true;
let b = false;
print(a && b);  // false
print(a || b);  // true
print(!a);      // false
print(!b);      // true
```

#### Short-Circuit Evaluation
```yeep
// && evaluates right operand only if left is true
print(false && "not printed");    // false

// || evaluates right operand only if left is false
print(true || "not evaluated");   // true
```

### String Concatenation
```yeep
let str1 = "Hello";
let str2 = "World";
let number = 42;
let boolean = true;

print(str1 + " " + str2);         // "Hello World"
print("Number: " + number);       // "Number: 42"
print("Boolean: " + boolean);     // "Boolean: true"
```

### Operator Precedence

From highest to lowest precedence:

1. `()` - Parentheses
2. `!` - Logical NOT
3. `*`, `/`, `%` - Multiplication, Division, Modulo
4. `+`, `-` - Addition, Subtraction
5. `<`, `<=`, `>`, `>=` - Comparison
6. `==`, `!=` - Equality
7. `&&` - Logical AND
8. `||` - Logical OR

```yeep
let result = 2 + 3 * 4;     // 14, not 20
let result2 = (2 + 3) * 4;  // 20
let bool = true || false && false;  // true
```

---

## 🔀 Control Flow

### If Statement

#### Basic If
```yeep
if (condition) {
    // statements
}
```

#### If-Else
```yeep
if (condition) {
    // statements if true
} else {
    // statements if false
}
```

#### Nested If-Else
```yeep
if (condition1) {
    // statements
} else {
    if (condition2) {
        // statements
    } else {
        // statements
    }
}
```

### While Loop
```yeep
while (condition) {
    // statements
    // make sure to update condition to avoid infinite loop
}
```

#### Example
```yeep
let i = 0;
while (i < 5) {
    print("Iteration: " + i);
    i = i + 1;
}
```

---

## 🎯 Functions

### Function Declaration
```yeep
fun functionName(parameter1, parameter2, ...) {
    // function body
    return value;  // optional
}
```

### Function Call
```yeep
functionName(argument1, argument2, ...);
```

### Examples

#### Function without Return Value
```yeep
fun greet(name) {
    print("Hello, " + name + "!");
}

greet("Alice");  // Hello, Alice!
```

#### Function with Return Value
```yeep
fun add(a, b) {
    return a + b;
}

let sum = add(5, 3);
print(sum);  // 8
```

#### Recursive Function
```yeep
fun factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

print(factorial(5));  // 120
```

### Function Parameters
- Functions can have zero or more parameters
- Parameters are local variables within the function
- Arguments are passed by value

```yeep
fun noParams() {
    print("No parameters needed!");
}

fun oneParam(x) {
    print("Received: " + x);
}

fun multipleParams(a, b, c) {
    return a + b + c;
}
```

---

## 🔧 Built-in Functions

### print(value)
Outputs a value to the console.

```yeep
print("Hello, World!");      // Hello, World!
print(42);                   // 42
print(true);                 // true
print(3.14159);             // 3.14159
```

**Note:** Currently `print` is the only built-in function. More may be added in future versions.

---

## 💬 Comments

Yeep supports C-style single-line comments:

```yeep
// This is a comment
let x = 42;  // End-of-line comment

// Multiple line comments
// can be written like this
let y = 10;
```

**Note:** Multi-line comments (`/* */`) are not currently supported.

---

## 📝 Grammar

### Formal Grammar (EBNF)

```ebnf
program        = statement* EOF

statement      = varDecl
               | funDecl
               | exprStmt
               | ifStmt
               | whileStmt
               | returnStmt

varDecl        = "let" IDENTIFIER "=" expression ";"

funDecl        = "fun" IDENTIFIER "(" parameters? ")" block

parameters     = IDENTIFIER ("," IDENTIFIER)*

exprStmt       = expression ";"

ifStmt         = "if" "(" expression ")" statement ("else" statement)?

whileStmt      = "while" "(" expression ")" statement

returnStmt     = "return" expression? ";"

block          = "{" statement* "}"

expression     = assignment

assignment     = IDENTIFIER "=" assignment
               | logic_or

logic_or       = logic_and ("||" logic_and)*

logic_and      = equality ("&&" equality)*

equality       = comparison (("==" | "!=") comparison)*

comparison     = term ((">" | ">=" | "<" | "<=") term)*

term           = factor (("+" | "-") factor)*

factor         = unary (("*" | "/" | "%") unary)*

unary          = ("!" | "-") unary
               | call

call           = primary ("(" arguments? ")")*

arguments      = expression ("," expression)*

primary        = NUMBER
               | STRING  
               | "true" | "false"
               | IDENTIFIER
               | "(" expression ")"

NUMBER         = DIGIT+ ("." DIGIT+)?
STRING         = '"' [^"]* '"'
IDENTIFIER     = ALPHA (ALPHA | DIGIT)*
ALPHA          = [a-zA-Z_]
DIGIT          = [0-9]
```

---

## 🚨 Error Handling

### Syntax Errors
```yeep
// Missing semicolon
let x = 42  // ERROR: Expected ';'

// Unmatched parentheses
print("Hello"  // ERROR: Expected ')'

// Invalid identifier
let 1name = "test";  // ERROR: Unexpected character
```

### Runtime Errors
```yeep
// Undefined variable
print(undefinedVar);  // ERROR: Undefined variable 'undefinedVar'

// Wrong number of arguments
fun add(a, b) { return a + b; }
add(1, 2, 3);  // ERROR: Expected 2 arguments but got 3
```

---

## 🔄 Type Conversion

### Implicit String Conversion
When using the `+` operator with strings, other types are automatically converted:

```yeep
print("Number: " + 42);       // "Number: 42"
print("Boolean: " + true);    // "Boolean: true"
print("Value: " + 3.14);      // "Value: 3.14"
```

### Boolean Context
In conditional expressions, values are converted to boolean:

```yeep
// Numbers: 0 is false, non-zero is true
if (0) { print("won't print"); }
if (1) { print("will print"); }

// Strings: empty string is false, non-empty is true  
if ("") { print("won't print"); }
if ("text") { print("will print"); }
```

---

## 🎯 Language Limitations

Current limitations that may be addressed in future versions:

1. **No arrays or collections**
2. **No objects or structs** 
3. **No modules or imports**
4. **No exception handling**
5. **Limited built-in functions**
6. **No file I/O operations**
7. **No standard library**

---

## 📚 See Also

- [**Language Tutorial**](Language-Tutorial) - Learn Yeep step by step
- [**Examples Gallery**](Examples-Gallery) - Practical code examples
- [**Best Practices**](Best-Practices) - Writing better Yeep code
- [**FAQ**](FAQ) - Common questions answered
