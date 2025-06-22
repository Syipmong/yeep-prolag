# 🎯 Yeep Programming Language - Official VSCode Extension

[![Version](https://img.shields.io/badge/version-2.0.1-brightgreen.svg)](https://marketplace.visualstudio.com/items?itemName=YipmongSaid.yeep-language)
[![Installs](https://img.shields.io/visual-studio-marketplace/i/YipmongSaid.yeep-language.svg)](https://marketplace.visualstudio.com/items?itemName=YipmongSaid.yeep-language)
[![Rating](https://img.shields.io/visual-studio-marketplace/stars/YipmongSaid.yeep-language.svg)](https://marketplace.visualstudio.com/items?itemName=YipmongSaid.yeep-language)
[![GitHub](https://img.shields.io/badge/GitHub-Yeep--Programming--Language-blue.svg?logo=github)](https://github.com/Syipmong/yeep-prolag)
[![Build Status](https://img.shields.io/github/actions/workflow/status/Syipmong/yeep-prolag/build.yml?branch=main&logo=github)](https://github.com/Syipmong/yeep-prolag/actions)
[![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/Syipmong/yeep-prolag/blob/main/LICENSE)

**The official Visual Studio Code extension for the Yeep Programming Language v2.0.1** - bringing modern syntax highlighting, intelligent code completion, and seamless development experience to your favorite editor.

## ✨ What is Yeep?

Yeep is a modern, interpreted programming language written in C++ that combines simplicity with powerful features:

- 🔢 **Dynamic typing** (numbers, strings, booleans, arrays)
- 📝 **Variables** with `let` declarations
- 🎯 **Functions** with `fun` keyword - clean and intuitive
- 🔀 **Control flow** (if/else, while loops, for loops)
- 🧠 **Logical operators** (`&&`, `||`, `!`, `and`, `or`, `not`)
- 📚 **Rich built-in functions** (print, str, sqrt, max, length, uppercase, etc.)
- 🌊 **Array manipulation** (push, get, size)
- 💬 **Interactive REPL** for live coding
- 🌍 **Cross-platform** (Windows, Linux, macOS)
- ⚡ **Modern C++ implementation** with optimized performance

## 🚀 Quick Start

### Installation

1. **Install from VSCode Marketplace**: [Yeep Language Extension](https://marketplace.visualstudio.com/items?itemName=YipmongSaid.yeep-language)
2. **Or install via Command Palette**: `Ctrl+Shift+P` → `Extensions: Install Extensions` → Search "Yeep"
3. **Or install via command line**:
   ```bash
   code --install-extension YipmongSaid.yeep-language
   ```

### Get Started in 30 Seconds

1. **Create a new file** with `.yeep` extension
2. **Start coding** with full syntax highlighting and IntelliSense
3. **Run your code** with `F5` or click the ▶️ **Play Button** in the top-right corner
4. **Debug your code** with `Ctrl+F5` or click the 🐛 **Debug Button**

## 🐛 NEW: Debug & Run Features (v2.0.5)

### Play Button Integration
- **▶️ Run Button**: Click the play button in the editor title bar to run your Yeep file instantly
- **🐛 Debug Button**: Click the debug button to start debugging with detailed output
- **Quick Access**: Right-click in editor → "▶️ Run Yeep File" or "🐛 Debug Yeep File"

### Keyboard Shortcuts
- **F5**: Run current Yeep file
- **Ctrl+F5**: Debug current Yeep file
- **Ctrl+Shift+Y**: Start Yeep REPL

### Enhanced Terminal Integration
- Integrated terminal output with colored syntax
- Error highlighting and stack traces
- REPL support with interactive commands

```yeep
// Hello World in Yeep!
print("Hello, World!");

// Variables and functions
let name = "Yeep Developer";
print("Welcome, " + name + "!");

fun greet(person) {
    return "Hello, " + person + "!";
}

print(greet("World"));
```

## 🎨 Features

### 🌈 Syntax Highlighting
- **Keywords**: `let`, `fun`, `if`, `else`, `while`, `for`, `return`
- **Built-in Functions**: `print`, `str`, `sqrt`, `max`, `length`, `uppercase`, `size`, `get`, `push`
- **Operators**: Arithmetic (`+`, `-`, `*`, `/`), Logical (`&&`, `||`, `!`), Comparison (`==`, `!=`, `<`, `>`)
- **Literals**: Numbers, strings, booleans, arrays
- **Comments**: Line comments with `//`

### 🧠 IntelliSense & Code Completion
- **Smart completions** for keywords and built-in functions
- **Parameter hints** for function calls
- **Variable suggestions** based on scope
- **Snippet support** for common patterns

### 📝 Code Snippets
Type these prefixes and press `Tab` to expand:

| Prefix | Snippet | Description |
|--------|---------|-------------|
| `print` | `print("message");` | Print statement |
| `let` | `let variable = value;` | Variable declaration |
| `fun` | `fun name(params) { ... }` | Function definition |
| `if` | `if (condition) { ... }` | If statement |
| `ifelse` | `if (condition) { ... } else { ... }` | If-else statement |
| `while` | `while (condition) { ... }` | While loop |
| `for` | `for (let i = 0; i < n; i = i + 1) { ... }` | For loop |
| `array` | `let arr = [elements];` | Array declaration |
| `comment` | `// comment` | Line comment |
| `hello` | `print("Hello, World!");` | Hello World |

### ⚡ Commands & Shortcuts

| Command | Shortcut | Description |
|---------|----------|-------------|
| `Yeep: Run File` | `F5` | Execute current Yeep file |
| `Yeep: Start REPL` | `Ctrl+Shift+Y` | Launch interactive REPL |

### 🎯 Language Features

#### Variables & Types
```yeep
let number = 42;
let text = "Hello, Yeep!";
let flag = true;
let items = [1, 2, 3, "mixed", true];
```

#### Functions
```yeep
fun add(a, b) {
    return a + b;
}

fun factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}
```

#### Control Flow
```yeep
// Conditional statements
if (x > 10) {
    print("x is large");
} else {
    print("x is small");
}

// Loops
let i = 0;
while (i < 5) {
    print("Count: " + str(i));
    i = i + 1;
}
```

#### Built-in Functions
```yeep
// String operations
print(length("Hello"));        // 5
print(uppercase("hello"));     // "HELLO"

// Math operations
print(sqrt(16));               // 4
print(max(10, 20, 5));        // 20

// Array operations
let arr = [1, 2, 3];
print(size(arr));             // 3
print(get(arr, 0));           // 1
print(push(arr, 4));          // [1, 2, 3, 4]
```

## 🛠️ Development Setup

### Prerequisites
- **Yeep Interpreter**: [Download from releases](https://github.com/Syipmong/yeep-prolag/releases/latest)
- **Visual Studio Code**: Version 1.74.0 or higher

### Building Yeep from Source
```bash
# Clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build for your platform
# Windows
./build_official.bat

# Linux/macOS
./build_official.sh

# Run a Yeep program
./build/yeep.exe your_program.yeep
```

## 📖 Language Documentation

| Resource | Description |
|----------|-------------|
| [🏠 Home](https://github.com/Syipmong/yeep-prolag/wiki/Home) | Project overview and quick start |
| [⚡ Installation Guide](https://github.com/Syipmong/yeep-prolag/wiki/Installation-Guide) | Complete installation instructions |
| [🎓 Language Tutorial](https://github.com/Syipmong/yeep-prolag/wiki/Language-Tutorial) | Step-by-step learning guide |
| [📖 Language Reference](https://github.com/Syipmong/yeep-prolag/wiki/Language-Reference) | Complete language specification |
| [📚 Standard Library](https://github.com/Syipmong/yeep-prolag/wiki/Standard-Library) | Built-in functions reference |
| [🎨 Examples Gallery](https://github.com/Syipmong/yeep-prolag/wiki/Examples-Gallery) | Code examples and use cases |

## 🎮 Try It Now!

Create a new file called `example.yeep` and try this code:

```yeep
// Yeep v2.0.1 Feature Demo
print("=== Welcome to Yeep! ===");

// Variables
let name = "Developer";
let age = 25;
let languages = ["Yeep", "C++", "JavaScript"];

// Function definition
fun introduce(person, years) {
    return "Hi! I'm " + person + ", " + str(years) + " years old.";
}

// Function calls and array operations
print(introduce(name, age));
print("I know " + str(size(languages)) + " languages:");

let i = 0;
while (i < size(languages)) {
    print("- " + get(languages, i));
    i = i + 1;
}

// Math operations
let numbers = [10, 25, 5, 40];
print("Max number: " + str(max(get(numbers, 0), get(numbers, 1), get(numbers, 2), get(numbers, 3))));
print("Square root of 16: " + str(sqrt(16)));

// String operations
let message = "yeep is awesome";
print("Uppercase: " + uppercase(message));
print("Length: " + str(length(message)));

print("=== Yeep Demo Complete! ===");
```

Press `F5` to run it and see Yeep in action! 🚀

## 🤝 Contributing

We welcome contributions! Here's how you can help:

1. **Report bugs**: [Open an issue](https://github.com/Syipmong/yeep-prolag/issues)
2. **Suggest features**: [Start a discussion](https://github.com/Syipmong/yeep-prolag/discussions)
3. **Contribute code**: [Submit a pull request](https://github.com/Syipmong/yeep-prolag/pulls)
4. **Improve docs**: Help us make the documentation better

## 📊 Extension Statistics

- **Total Downloads**: ![Downloads](https://img.shields.io/visual-studio-marketplace/d/YipmongSaid.yeep-language)
- **Active Installs**: ![Installs](https://img.shields.io/visual-studio-marketplace/i/YipmongSaid.yeep-language)
- **User Rating**: ![Rating](https://img.shields.io/visual-studio-marketplace/stars/YipmongSaid.yeep-language)

## 🔗 Links

- **🏠 Homepage**: [Yeep Programming Language](https://github.com/Syipmong/yeep-prolag)
- **📖 Documentation**: [Wiki](https://github.com/Syipmong/yeep-prolag/wiki)
- **💾 Downloads**: [Releases](https://github.com/Syipmong/yeep-prolag/releases)
- **🐛 Issues**: [Bug Reports](https://github.com/Syipmong/yeep-prolag/issues)
- **💬 Discussions**: [Community](https://github.com/Syipmong/yeep-prolag/discussions)

## 📄 License

This extension is licensed under the [MIT License](https://github.com/Syipmong/yeep-prolag/blob/main/LICENSE).

---

**🎯 Happy coding with Yeep!** 

*Made with ❤️ by the Yeep community*
