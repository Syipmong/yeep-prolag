# Yeep Programming Language Grammar Specification

## Overview
This document defines the formal grammar for the Yeep programming language using Extended Backus-Naur Form (EBNF) notation.

## Notation
- `|` indicates alternative productions
- `[]` indicates optional elements
- `{}` indicates zero or more repetitions
- `()` indicates grouping
- `terminal` indicates terminal symbols (tokens)
- `<non-terminal>` indicates non-terminal symbols

## Lexical Grammar (Tokens)

### Keywords
```
LET       ::= "let"
FUN       ::= "fun"
IF        ::= "if"
ELSE      ::= "else"
WHILE     ::= "while"
FOR       ::= "for"
RETURN    ::= "return"
TRUE      ::= "true"
FALSE     ::= "false"
PRINT     ::= "print"
AND       ::= "and"
OR        ::= "or"
NOT       ::= "not"
BREAK     ::= "break"
CONTINUE  ::= "continue"
```

### Operators
```
PLUS      ::= "+"
MINUS     ::= "-"
MULTIPLY  ::= "*"
DIVIDE    ::= "/"
MODULO    ::= "%"
POWER     ::= "**"
ASSIGN    ::= "="
EQUAL     ::= "=="
NOT_EQUAL ::= "!="
LESS      ::= "<"
GREATER   ::= ">"
LESS_EQ   ::= "<="
GREATER_EQ ::= ">="
LOGICAL_AND ::= "&&"
LOGICAL_OR  ::= "||"
LOGICAL_NOT ::= "!"
INCREMENT   ::= "++"
DECREMENT   ::= "--"
PLUS_ASSIGN ::= "+="
MINUS_ASSIGN ::= "-="
```

### Delimiters
```
LEFT_PAREN    ::= "("
RIGHT_PAREN   ::= ")"
LEFT_BRACE    ::= "{"
RIGHT_BRACE   ::= "}"
LEFT_BRACKET  ::= "["
RIGHT_BRACKET ::= "]"
COMMA         ::= ","
SEMICOLON     ::= ";"
DOT           ::= "."
COLON         ::= ":"
ARROW         ::= "=>"
```

### Literals
```
NUMBER     ::= INTEGER | FLOAT
INTEGER    ::= [0-9]+
FLOAT      ::= [0-9]+ "." [0-9]+
STRING     ::= '"' ([^"\\] | ESCAPE_SEQUENCE)* '"'
IDENTIFIER ::= [a-zA-Z_][a-zA-Z0-9_]*
BOOLEAN    ::= TRUE | FALSE
```

### Special
```
NEWLINE   ::= "\n"
EOF       ::= end-of-file
COMMENT   ::= "//" [^\n]* NEWLINE
```

## Syntactic Grammar

### Program Structure
```
program ::= { statement | NEWLINE }

statement ::= declaration_statement
           | expression_statement
           | control_statement
           | block_statement

block_statement ::= "{" { statement | NEWLINE } "}"
```

### Declarations
```
declaration_statement ::= variable_declaration
                       | function_declaration

variable_declaration ::= LET IDENTIFIER "=" expression ";"

function_declaration ::= FUN IDENTIFIER "(" parameter_list? ")" block_statement

parameter_list ::= IDENTIFIER { "," IDENTIFIER }
```

### Expressions
```
expression ::= assignment_expression

assignment_expression ::= logical_or_expression [ assignment_operator assignment_expression ]

assignment_operator ::= "=" | "+=" | "-=" | "*=" | "/=" | "%="

logical_or_expression ::= logical_and_expression { "||" logical_and_expression }

logical_and_expression ::= equality_expression { "&&" equality_expression }

equality_expression ::= relational_expression { ("==" | "!=") relational_expression }

relational_expression ::= additive_expression { ("<" | ">" | "<=" | ">=") additive_expression }

additive_expression ::= multiplicative_expression { ("+" | "-") multiplicative_expression }

multiplicative_expression ::= power_expression { ("*" | "/" | "%") power_expression }

power_expression ::= unary_expression [ "**" power_expression ]

unary_expression ::= ("!" | "-" | "+") unary_expression
                   | postfix_expression

postfix_expression ::= primary_expression { postfix_operator }

postfix_operator ::= "++"
                  | "--"
                  | "(" argument_list? ")"
                  | "[" expression "]"
                  | "." IDENTIFIER

primary_expression ::= IDENTIFIER
                    | NUMBER
                    | STRING
                    | BOOLEAN
                    | "(" expression ")"
                    | array_literal
                    | object_literal

array_literal ::= "[" [ expression { "," expression } ] "]"

object_literal ::= "{" [ property { "," property } ] "}"

property ::= IDENTIFIER ":" expression
          | STRING ":" expression

argument_list ::= expression { "," expression }
```

### Control Flow
```
control_statement ::= if_statement
                   | while_statement
                   | for_statement
                   | return_statement
                   | break_statement
                   | continue_statement

if_statement ::= IF "(" expression ")" statement [ ELSE statement ]

while_statement ::= WHILE "(" expression ")" statement

for_statement ::= FOR "(" [ variable_declaration | expression ] ";" 
                         [ expression ] ";" 
                         [ expression ] ")" statement

return_statement ::= RETURN [ expression ] ";"

break_statement ::= BREAK ";"

continue_statement ::= CONTINUE ";"
```

### Other Statements
```
expression_statement ::= expression ";"
```

## Operator Precedence (Highest to Lowest)
1. `()` `[]` `.` (postfix operators)
2. `++` `--` (postfix)
3. `!` `-` `+` (unary operators)
4. `**` (power, right-associative)
5. `*` `/` `%` (multiplicative)
6. `+` `-` (additive)
7. `<` `>` `<=` `>=` (relational)
8. `==` `!=` (equality)
9. `&&` (logical AND)
10. `||` (logical OR)
11. `=` `+=` `-=` `*=` `/=` `%=` (assignment, right-associative)

## Type System

### Basic Types
- `number` - Both integers and floating-point numbers
- `string` - Text data
- `boolean` - True/false values
- `array` - Ordered collections
- `object` - Key-value mappings
- `function` - Callable entities
- `null` - Absence of value

### Type Coercion Rules
1. Arithmetic operations coerce to numbers
2. String concatenation with `+` converts other types to strings
3. Logical operations coerce to booleans
4. Comparison operations follow JavaScript-like rules

## Semantics

### Variable Scoping
- Block-scoped variables with `let`
- Function parameters are local to the function
- Nested scopes can access outer scope variables
- No variable hoisting

### Function Semantics
- Functions are first-class values
- Support for closures
- Recursive functions allowed
- Optional return values (implicitly return `null`)

### Control Flow Semantics
- `if` statements evaluate condition for truthiness
- `while` loops continue while condition is truthy
- `for` loops provide C-style iteration
- `break` and `continue` work in loops only

### Error Handling
- Runtime errors for undefined variables
- Type errors for invalid operations
- Stack overflow protection for recursion
- Division by zero handling

## Examples

### Variable Declaration
```yeep
let x = 10;
let name = "Yeep";
let isActive = true;
```

### Function Declaration
```yeep
fun add(a, b) {
    return a + b;
}

fun greet(name) {
    print("Hello, " + name + "!");
}
```

### Control Flow
```yeep
if (score >= 90) {
    print("Excellent!");
} else if (score >= 70) {
    print("Good job!");
} else {
    print("Keep trying!");
}

while (count < 10) {
    print(count);
    count = count + 1;
}
```

### Arrays and Objects
```yeep
let numbers = [1, 2, 3, 4, 5];
let person = {
    name: "Alice",
    age: 30,
    active: true
};

print(numbers[0]);
print(person.name);
```

## Future Extensions

### Planned Features
1. **Classes and Objects**
   ```yeep
   class Person {
       fun init(name, age) {
           this.name = name;
           this.age = age;
       }
       
       fun greet() {
           print("Hi, I'm " + this.name);
       }
   }
   ```

2. **Modules and Imports**
   ```yeep
   import { math } from "std/math";
   import utils from "./utils.yeep";
   ```

3. **Exception Handling**
   ```yeep
   try {
       risky_operation();
   } catch (error) {
       print("Error: " + error.message);
   } finally {
       cleanup();
   }
   ```

4. **Advanced Types**
   ```yeep
   let optional: number? = null;
   let callback: (number, number) => number = add;
   ```

5. **Pattern Matching**
   ```yeep
   match value {
       case 0 => print("zero");
       case 1..10 => print("small number");
       case _ => print("other");
   }
   ```

---

*This grammar specification provides a solid foundation for the Yeep programming language while allowing for future extensions and improvements.*
