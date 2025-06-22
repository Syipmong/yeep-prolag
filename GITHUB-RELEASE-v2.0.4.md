# 🚀 Yeep Programming Language v2.0.4

**Major Feature Release - File I/O, System Integration & Enhanced REPL**

---

## 🆕 **What's New in v2.0.4**

### 📁 **File I/O Operations (NEW!)**
- **`writeFile(filename, content)`** - Write text content to files
- **`readFile(filename)`** - Read complete file contents
- **`fileExists(filename)`** - Check file existence
- Full file system integration for data persistence and configuration

### 🔧 **System Integration (NEW!)**
- **`env(variable_name)`** - Access environment variables
- **`now()`** - Get current Unix timestamp
- **`exec(command)`** - Execute system commands
- Cross-platform support for Windows, Linux, and macOS

### 🎮 **Enhanced REPL Commands (NEW!)**
- **`vars`** - Display all variables in current session with types
- **`funcs`** - Display all user-defined functions with signatures
- **`features`** - Show new v2.0.4 features
- **`examples`** - Interactive code examples
- **`clear`** - Clear screen, **`help`** - Show all commands

---

## 💡 **Quick Examples**

### File Operations
```yeep
// Write configuration
writeFile("config.txt", "version=2.0.4\nauthor=Yeep Team");

// Read and display
print(readFile("config.txt"));

// Check existence
if (fileExists("config.txt")) {
    print("Config found!");
}
```

### System Integration
```yeep
// Environment access
print("User: " + env("USERNAME"));
print("Home: " + env("USERPROFILE"));

// Timestamps
print("Current time: " + str(now()));

// System commands
exec("echo 'Hello from Yeep!' >> log.txt");
```

### Enhanced REPL
```
yeep> let numbers = [1, 2, 3, 4, 5];
yeep> fun double(x) { return x * 2; }
yeep> vars
🔍 Global Variables:
  numbers = [1.000000, 2.000000, 3.000000, 4.000000, 5.000000]
yeep> funcs
🔍 User-Defined Functions:
  fun double(x)
yeep> features
🚀 New Features in Yeep v2.0.4: [displays complete feature list]
```

---

## ✅ **Complete Feature Set**

- **🎮 Interactive REPL** - Colorized, feature-rich development environment
- **🔄 Control Flow** - for loops, while loops, conditionals with proper scoping
- **📝 User Functions** - Parameters, return values, recursion support
- **📊 Variable Types** - Numbers, strings, arrays, booleans
- **🧮 Built-in Functions** - 15+ math, string, and utility functions
- **📁 File I/O** - Complete file system operations
- **🔧 System Access** - Environment variables and command execution
- **🌐 Cross-platform** - Windows, Linux, macOS native support

---

## 🏗️ **Installation**

### Windows
```cmd
# Extract the ZIP file and run:
install.bat
```

### Linux/macOS
```bash
# Extract the archive and run:
sudo ./install.sh
```

### Verification
```bash
yeep --version
# Output: Yeep Programming Language v2.0.4

yeep examples/feature_showcase.yeep
# Runs complete feature demonstration
```

---

## 📦 **What's Included**

- **`yeep.exe`** / **`yeep`** - Main interpreter (optimized build)
- **Installation scripts** - Windows (`install.bat`) and Unix (`install.sh`)
- **Complete documentation** - Installation guide, user manual, release notes
- **Example scripts** - Feature showcase and sample programs
- **VSCode extension** - Syntax highlighting for development
- **Uninstaller** - Clean removal system

---

## 🎯 **Upgrade Benefits**

### From v2.0.3 → v2.0.4
- ✅ **File persistence** - Save and load data between program runs
- ✅ **System integration** - Access environment and execute commands
- ✅ **Better development** - Enhanced REPL with variable/function inspection
- ✅ **Production ready** - Stable, tested, optimized performance

### Backward Compatibility
- ✅ **100% compatible** - All v2.0.3 scripts work unchanged
- ✅ **Additive features** - New functionality doesn't break existing code
- ✅ **Same syntax** - No learning curve for existing users

---

## 🧪 **Quality Assurance**

- ✅ **Thoroughly tested** - All features verified on Windows, Linux, macOS
- ✅ **Production stable** - Optimized C++17 implementation
- ✅ **Memory safe** - Proper resource management and cleanup
- ✅ **Cross-platform** - Native builds for all major operating systems

---

## 📚 **Resources**

- **📖 [Complete Documentation](https://github.com/Syipmong/yeep-prolag/blob/main/README.md)**
- **🚀 [Installation Guide](https://github.com/Syipmong/yeep-prolag/blob/main/INSTALLATION-GUIDE.md)**
- **💡 [Language Examples](https://github.com/Syipmong/yeep-prolag/tree/main/examples)**
- **🎯 [Feature Showcase](https://github.com/Syipmong/yeep-prolag/blob/main/feature_showcase_v2.0.4.yeep)**

---

## 🎉 **Ready for Production Use!**

Yeep v2.0.4 represents a major milestone - it's **feature-complete**, **stable**, and **ready for real-world applications**. Download, install, and start building with Yeep today!

**Happy coding! 🎯**
