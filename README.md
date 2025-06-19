# Yeep Programming Language

A simple, interpreted programming language written in C.

## Features

- Dynamic typing
- Variables and expressions
- Control flow (if/else, while loops)
- Functions
- Built-in data types (numbers, strings, booleans)
- Interactive shell (REPL)

## Building

```bash
gcc -o yeep src/*.c -I include
```

## Running

```bash
# Interactive shell
./yeep

# Run a file
./yeep script.yeep
```

## Language Syntax

### Variables
```yeep
let x = 42;
let name = "Hello, World!";
let flag = true;
```

### Functions
```yeep
fun greet(name) {
    print("Hello, " + name + "!");
}

greet("Yeep");
```

### Control Flow
```yeep
if (x > 10) {
    print("x is greater than 10");
} else {
    print("x is 10 or less");
}

while (x > 0) {
    print(x);
    x = x - 1;
}
```

## Project Structure

- `src/` - Source code
- `include/` - Header files
- `examples/` - Example Yeep programs
- `tests/` - Test files
