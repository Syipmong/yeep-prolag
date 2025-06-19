# Yeep Programming Language

A simple, interpreted programming language written in C with support for variables, functions, control flow, and logical operators.

## 📥 Download

**Latest Release:** [Download Yeep v1.0.0](https://github.com/syipmong/yeep-prolag/releases/latest)

| Platform | Download | 
|----------|----------|
| 🪟 **Windows** | [yeep-windows-x64.zip](https://github.com/syipmong/yeep-prolag/releases/latest/download/yeep-windows-x64.zip) |
| 🐧 **Linux** | [yeep-linux-x64.tar.gz](https://github.com/syipmong/yeep-prolag/releases/latest/download/yeep-linux-x64.tar.gz) |
| 🍎 **macOS** | [yeep-macos-x64.tar.gz](https://github.com/syipmong/yeep-prolag/releases/latest/download/yeep-macos-x64.tar.gz) |

> **💡 Tip:** After downloading, follow the [installation instructions](#-easy-installation-recommended) below.

## ✨ Features

- 🔢 **Dynamic typing** - Numbers, strings, booleans
- 📝 **Variables and expressions** - Let bindings and arithmetic
- 🔀 **Control flow** - If/else statements and while loops  
- 🎯 **Functions** - Define and call custom functions
- 🧠 **Logical operators** - `&&`, `||`, `!` with short-circuit evaluation
- 🔗 **String concatenation** - Combine strings with any data type
- 💬 **Interactive shell (REPL)** - Test code interactively
- 📜 **Shebang support** - Make executable scripts (`#!/usr/bin/env yeep`)
- 🛠️ **Professional CLI** - `--help`, `--version`, file execution
- 🎯 **Cross-platform** - Windows, Linux, macOS

## Quick Start

### 🚀 Easy Installation (Recommended)

#### One-Line Install (Linux/macOS)
```bash
curl -fsSL https://raw.githubusercontent.com/syipmong/yeep-prolag/main/install-quick.sh | bash
```

#### Download from GitHub Releases

1. **Go to [Releases](https://github.com/YOUR_USERNAME/yeep-prolag/releases)**
2. **Download the latest version** for your platform:
   - **Windows**: `yeep-windows-x64.zip`
   - **Linux**: `yeep-linux-x64.tar.gz`
   - **macOS**: `yeep-macos-x64.tar.gz`

3. **Extract and install**:

   **Windows:**
   ```cmd
   # Extract the ZIP file
   # Right-click "install.bat" → "Run as administrator"
   install.bat
   ```

   **Linux/macOS:**
   ```bash
   # Extract the archive
   tar -xzf yeep-linux-x64.tar.gz  # or yeep-macos-x64.tar.gz
   cd yeep-linux-x64               # or yeep-macos-x64
   
   # Install for current user
   chmod +x install.sh
   ./install.sh
   
   # OR install system-wide
   sudo ./install.sh
   ```

4. **Verify installation**:
   ```bash
   yeep --version
   ```

### 🛠️ Build from Source

#### Prerequisites
- GCC compiler
- Make (Linux/macOS) or MinGW/MSYS2 (Windows)

#### Steps
```bash
# Clone the repository
git clone https://github.com/syipmong/yeep-prolag.git
cd yeep-prolag

# Build
make clean && make

# Install (Linux/macOS)
sudo make install

# Or install with script
chmod +x install.sh
sudo ./install.sh
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

## 📖 Language Syntax

### Variables
```yeep
let x = 42;
let name = "Hello, World!";
let flag = true;
```

### Logical Operators
```yeep
let a = true;
let b = false;

print("AND: " + (a && b));    // AND: false
print("OR: " + (a || b));     // OR: true
print("NOT: " + (!a));        // NOT: false

// Short-circuit evaluation
print(false && "not printed"); // false
print(true || "not evaluated"); // true
```

### String Concatenation
```yeep
let name = "Yeep";
let version = 1.0;
let active = true;

print("Language: " + name);      // Language: Yeep
print("Version: " + version);    // Version: 1
print("Active: " + active);      // Active: true
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

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

- 🐛 [Report bugs](https://github.com/syipmong/yeep-prolag/issues/new?template=bug_report.md)
- 💡 [Request features](https://github.com/syipmong/yeep-prolag/issues/new?template=feature_request.md)
- 🔧 [Submit pull requests](https://github.com/syipmong/yeep-prolag/pulls)

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🌟 Acknowledgments

- Built with ❤️ for learning and exploring programming language design
- Inspired by modern scripting languages and classic language implementation techniques
- Created by **Yipmong Said**, Student at Baze University Nigeria

## 👨‍💻 Author

**Yipmong Said**  
🎓 Student at Baze University Nigeria  
🐙 GitHub: [@syipmong](https://github.com/syipmong)

---

**⭐ Star this repo if you find Yeep useful!**

**📥 [Download the latest release](https://github.com/syipmong/yeep-prolag/releases/latest)** | **📖 [Read the docs](README.md)** | **🤝 [Contribute](CONTRIBUTING.md)**
