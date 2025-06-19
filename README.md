# Yeep Programming Language

[![Build and Release](https://github.com/Syipmong/yeep-prolag/actions/workflows/build.yml/badge.svg)](https://github.com/Syipmong/yeep-prolag/actions/workflows/build.yml)
[![Latest Release](https://img.shields.io/github/v/release/Syipmong/yeep-prolag?color=blue&logo=github)](https://github.com/Syipmong/yeep-prolag/releases/latest)
[![License](https://img.shields.io/github/license/Syipmong/yeep-prolag?color=green)](https://github.com/Syipmong/yeep-prolag/blob/main/LICENSE)
[![Platform Support](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey?logo=windows&logoColor=white)](https://github.com/Syipmong/yeep-prolag/releases/latest)
[![Language](https://img.shields.io/badge/language-C++-blue?logo=cplusplus)](https://github.com/Syipmong/yeep-prolag)
[![Status](https://img.shields.io/badge/status-WORKING%20✅-brightgreen)](https://github.com/Syipmong/yeep-prolag)
[![GitHub Stars](https://img.shields.io/github/stars/Syipmong/yeep-prolag?style=social)](https://github.com/Syipmong/yeep-prolag/stargazers)
[![GitHub Forks](https://img.shields.io/github/forks/Syipmong/yeep-prolag?style=social)](https://github.com/Syipmong/yeep-prolag/network/members)

A simple, interpreted programming language **now written in modern C++** with support for variables, functions, control flow, and logical operators.

## 🎉 C++ Migration Complete!

**The Yeep interpreter has been successfully migrated from C to C++ and is now fully functional!**

### Quick Start
```bash
# Build
g++ -Wall -Wextra -std=c++17 -I include build/main.o build/core/YeepEngine.o build/core/Token.o build/core/Lexer.o -o build/yeep.exe

# Run interactive mode
./build/yeep.exe

# Run a script
./build/yeep.exe script.yeep
```

### Working Features ✅
- Interactive REPL with help and version commands
- File execution for `.yeep` scripts
- Print statements: `print("Hello, World!");`
- Proper error handling and reporting
- Modern C++ architecture with smart pointers and exception handling

## � Documentation

**[📖 Comprehensive Wiki Documentation](https://github.com/Syipmong/yeep-prolag/wiki)**

| Documentation | Description |
|---------------|-------------|
| [🏠 Home](https://github.com/Syipmong/yeep-prolag/wiki/Home) | Project overview and quick start |
| [⚡ Installation Guide](https://github.com/Syipmong/yeep-prolag/wiki/Installation-Guide) | Complete installation instructions |
| [🎓 Language Tutorial](https://github.com/Syipmong/yeep-prolag/wiki/Language-Tutorial) | Step-by-step learning guide |
| [📖 Language Reference](https://github.com/Syipmong/yeep-prolag/wiki/Language-Reference) | Complete language specification |
| [📚 Standard Library](https://github.com/Syipmong/yeep-prolag/wiki/Standard-Library) | Built-in functions and features |
| [🎨 Examples Gallery](https://github.com/Syipmong/yeep-prolag/wiki/Examples-Gallery) | Code examples and use cases |
| [🏆 Showcase](https://github.com/Syipmong/yeep-prolag/wiki/Showcase) | Community projects and highlights |
| [🔧 Troubleshooting](https://github.com/Syipmong/yeep-prolag/wiki/Troubleshooting) | Common issues and solutions |
| [❓ FAQ](https://github.com/Syipmong/yeep-prolag/wiki/FAQ) | Frequently asked questions |
| [🤝 Contributing Guide](https://github.com/Syipmong/yeep-prolag/wiki/Contributing-Guide) | How to contribute to the project |

## �📥 Download

**Latest Release:** [Download Yeep v1.0.0](https://github.com/Syipmong/yeep-prolag/releases/latest)

| Platform | Download | 
|----------|----------|
| 🪟 **Windows** | [yeep-windows-x64.zip](https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-windows-x64.zip) |
| 🐧 **Linux** | [yeep-linux-x64.tar.gz](https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-linux-x64.tar.gz) |
| 🍎 **macOS** | [yeep-macos-x64.tar.gz](https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-macos-x64.tar.gz) |

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
curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-quick.sh | bash
```

#### Download from GitHub Releases

1. **Go to [Releases](https://github.com/Syipmong/yeep-prolag/releases)**
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

### 🎯 After Installation - How to Use Yeep

Once installed, you can run Yeep from any command prompt:

```cmd
# Start interactive shell (REPL)
yeep

# Run a Yeep script file  
yeep script.yeep

# Show help and version
yeep --help
yeep --version

# Run example programs
yeep examples/hello.yeep
```

**📁 Installation Locations:**
- **Windows System**: `C:\Program Files\Yeep\`
- **Windows User**: `C:\Users\YourName\Yeep\`
- **Linux/macOS**: `/usr/local/bin/yeep`

**🗑️ To Uninstall:**
- **Windows**: Run `uninstall.bat` from installation directory
- **Linux/macOS**: Run `sudo make uninstall` or delete files manually

> 📖 **See [USAGE.md](USAGE.md) for detailed usage guide and troubleshooting**

### ⚠️ Windows Installation Troubleshooting

If you encounter issues during Windows installation:

#### ❌ **"build.bat is not recognized" Error**
This means you downloaded the source code instead of the release.

**Solution:**
1. Go to [Releases](https://github.com/Syipmong/yeep-prolag/releases/latest)
2. Download `yeep-windows-x64.zip` (not the source code)
3. Extract the ZIP file completely
4. Look for `yeep.exe` in the extracted folder
5. Run `install.bat` as administrator

#### ❌ **"msys-2.0.dll was not found" Error**
This was a known issue in older versions, now fixed!

**Solution:**
- Download the latest release (v1.0.1 or newer)
- The new version includes static linking (no DLL dependencies)

#### ❌ **"Download was unexpected at this time" Error**
This was a batch file syntax issue in older versions, now fixed!

**Solution:**
- Download the latest release (v1.0.6 or newer)
- If still having issues, try the alternative installers: `install-simple.bat` or `install-debug.bat`

#### ❌ **"Installation failed" Error**
**Solution:**
- Make sure you extracted **all files** from the ZIP
- Run `install.bat` as **administrator**
- Check that `yeep.exe` exists in the same folder as `install.bat`

### 🛠️ Build from Source

#### Prerequisites
- GCC compiler
- Make (Linux/macOS) or MinGW/MSYS2 (Windows)

#### Steps
```bash
# Clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
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

---

## 📊 Project Status

[![GitHub Issues](https://img.shields.io/github/issues/Syipmong/yeep-prolag?color=orange&logo=github)](https://github.com/Syipmong/yeep-prolag/issues)
[![GitHub Pull Requests](https://img.shields.io/github/issues-pr/Syipmong/yeep-prolag?color=blue&logo=github)](https://github.com/Syipmong/yeep-prolag/pulls)
[![Last Commit](https://img.shields.io/github/last-commit/Syipmong/yeep-prolag?color=green&logo=git)](https://github.com/Syipmong/yeep-prolag/commits/main)
[![Repo Size](https://img.shields.io/github/repo-size/Syipmong/yeep-prolag?color=lightblue&logo=github)](https://github.com/Syipmong/yeep-prolag)
[![Code Size](https://img.shields.io/github/languages/code-size/Syipmong/yeep-prolag?color=purple&logo=c)](https://github.com/Syipmong/yeep-prolag)
[![Downloads](https://img.shields.io/github/downloads/Syipmong/yeep-prolag/total?color=brightgreen&logo=download)](https://github.com/Syipmong/yeep-prolag/releases)

## Project Structure

- `src/` - Source code
- `include/` - Header files
- `examples/` - Example Yeep programs
- `tests/` - Test files

## 🤝 Contributing

We welcome contributions! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

- 🐛 [Report bugs](https://github.com/Syipmong/yeep-prolag/issues/new?template=bug_report.md)
- 💡 [Request features](https://github.com/Syipmong/yeep-prolag/issues/new?template=feature_request.md)
- 🔧 [Submit pull requests](https://github.com/Syipmong/yeep-prolag/pulls)

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

**📥 [Download the latest release](https://github.com/Syipmong/yeep-prolag/releases/latest)** | **📖 [Read the docs](README.md)** | **🤝 [Contribute](CONTRIBUTING.md)**
