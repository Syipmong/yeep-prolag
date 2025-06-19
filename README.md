# Yeep Programming Language

A simple, interpreted programming language written in C.

## Features

- Dynamic typing
- Variables and expressions
- Control flow (if/else, while loops)  
- Functions
- Built-in data types (numbers, strings, booleans)
- Interactive shell (REPL)
- Shebang support for executable scripts

## Quick Start

### Installation

#### Windows
1. Download or clone the repository
2. Run the installer as administrator:
```cmd
install.bat
```

#### Linux/macOS
1. Download or clone the repository
2. Run the installer:
```bash
chmod +x install.sh
./install.sh
```

Or for system-wide installation:
```bash
sudo ./install.sh
```

#### Manual Installation (All platforms)
```bash
# Build from source
make clean && make

# Install (Linux/macOS)
sudo make install

# Or copy manually to your PATH
cp build/yeep /usr/local/bin/
```

### Usage

```bash
# Interactive shell
yeep

# Run a script
yeep script.yeep

# Run with shebang (Linux/macOS)
chmod +x script.yeep
./script.yeep

# Show help
yeep --help

# Show version
yeep --version
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
