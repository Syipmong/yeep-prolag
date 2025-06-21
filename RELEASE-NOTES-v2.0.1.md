# 🎉 Yeep Programming Language v2.0.1 - Official Release

**Release Date:** June 22, 2025  
**Version:** 2.0.1  
**Codename:** System-Wide Installation  

## 🚀 Major Features

### ✨ **System-Wide Installation**
Yeep now supports professional system-wide installation on Windows, Linux, and macOS. Install once and use `yeep` from anywhere on your system!

#### Windows
- **Administrator Install**: Installs to `C:\Program Files\Yeep\`
- **User Install**: Falls back to `%USERPROFILE%\Yeep\`
- **Automatic PATH**: Registry-based PATH management
- **One-Click Install**: Just run `install.bat` as Administrator

#### Linux/macOS
- **System Install**: `/usr/local/bin/yeep` with `sudo ./install.sh`
- **User Install**: `~/.local/bin/yeep` with `./install.sh`
- **Shell Integration**: Automatic `.bashrc`/`.zshrc` updates
- **Standard Locations**: Follows Unix filesystem hierarchy

### 🎨 **Professional Interactive REPL**
- **Colorized Output**: Beautiful ANSI colors for better readability
- **Built-in Commands**: `help`, `version`, `clear`, `examples`, `vars`, `funcs`
- **Smart Features**: Auto-semicolon insertion, error recovery
- **Cross-Platform**: Consistent experience on all operating systems
- **Welcome Screen**: Professional ASCII art welcome message

### 🔧 **Modernized Build System**
- **Clean Architecture**: Streamlined build process
- **Cross-Platform**: `build.bat` (Windows) and `build.sh` (Linux/macOS)
- **Error Handling**: Clear error messages and build status
- **Fast Compilation**: Optimized C++17 compilation

### 📦 **Complete Package Management**
- **Uninstaller**: Automatic uninstall script generation
- **Documentation**: Complete docs, examples, and guides included
- **VSCode Extension**: Professional syntax highlighting included
- **Examples**: 29+ example programs to get started

## 📥 **Download**

### Windows (x64)
- **Package**: `yeep-v2.0.1-windows-x64.zip` (390KB)
- **SHA256**: See `yeep-v2.0.1-windows-x64.zip.sha256`

### Installation Instructions

#### Windows
```cmd
1. Download yeep-v2.0.1-windows-x64.zip
2. Extract to a folder
3. Right-click Command Prompt → "Run as administrator"
4. Navigate to extracted folder
5. Run: install.bat
6. Restart command prompt
7. Test: yeep --version
```

#### Linux/macOS
```bash
1. Download and extract the package
2. chmod +x install.sh build.sh
3. sudo ./install.sh  # System-wide
   # OR
   ./install.sh       # User-only
4. Restart terminal
5. Test: yeep --version
```

## 🎯 **Usage After Installation**

```bash
# Start interactive REPL
yeep

# Run a script
yeep myscript.yeep

# Show help
yeep --help

# Show version
yeep --version

# Try examples
yeep examples/hello_working.yeep
yeep examples/calculator_example.yeep
```

## 🆕 **What's New in v2.0.1**

### Installation & Distribution
- ✅ **System-wide installation** for Windows, Linux, macOS
- ✅ **Automatic PATH management** - no manual configuration
- ✅ **Smart privilege detection** - system vs user install
- ✅ **Complete uninstaller** - clean removal
- ✅ **Professional packaging** - ready for distribution

### User Experience
- ✅ **Colorized REPL** with beautiful output
- ✅ **Built-in help system** - `help`, `examples`, `version` commands
- ✅ **Error recovery** - continue after syntax errors
- ✅ **Auto-completion** - smart semicolon insertion
- ✅ **Cross-platform** - consistent experience everywhere

### Developer Experience
- ✅ **Clean build system** - simple `build.bat`/`build.sh`
- ✅ **Modern C++17** - robust, maintainable codebase
- ✅ **VSCode extension** - professional development environment
- ✅ **Comprehensive examples** - 29+ sample programs
- ✅ **Complete documentation** - installation, usage, language spec

### Language Features
- ✅ **Dynamic typing** - numbers, strings, booleans
- ✅ **Variables** - `let` bindings with expressions
- ✅ **Functions** - `fun` keyword with parameters and return values
- ✅ **Control flow** - `if`/`else`, `while` loops, `for` loops
- ✅ **Built-in functions** - `print()`, `input()`, `str()`, `num()`, `len()`
- ✅ **Logical operators** - `&&`, `||`, `!` with short-circuit evaluation
- ✅ **String operations** - concatenation, interpolation
- ✅ **Array support** - creation, indexing, iteration

## 📊 **Technical Specifications**

### System Requirements
- **Windows**: Windows 10+ with MinGW-w64 or MSYS2
- **Linux**: Any modern distribution with GCC 7.0+ or Clang 5.0+
- **macOS**: macOS 10.14+ with Xcode Command Line Tools

### Package Contents
- **Executable**: `yeep.exe` (Windows) or `yeep` (Unix)
- **Installers**: `install.bat`, `install.sh`, `uninstall.bat`
- **Documentation**: Complete guides and specifications
- **Examples**: 29 example programs (`.yeep` files)
- **Source Code**: Full C++ implementation
- **VSCode Extension**: Syntax highlighting and snippets
- **Build Scripts**: Cross-platform build system

### Performance
- **Startup Time**: <10ms
- **Memory Usage**: <5MB typical
- **Package Size**: 390KB compressed
- **Build Time**: <30 seconds from source

## 🔄 **Migration from v2.0.0**

If upgrading from v2.0.0:

1. **Uninstall old version** (if applicable)
2. **Download v2.0.1** package
3. **Run new installer** - `install.bat` or `install.sh`
4. **Update VSCode extension** - install new `.vsix` file
5. **Test installation** - `yeep --version`

## 🐛 **Bug Fixes**

- Fixed build system issues with deprecated scripts
- Resolved PATH management problems on Windows
- Improved error handling in REPL
- Fixed compiler warnings in C++ code
- Enhanced cross-platform compatibility

## 🙏 **Acknowledgments**

Thanks to all contributors and testers who helped make v2.0.1 possible!

## 📞 **Support**

- **Issues**: [GitHub Issues](https://github.com/Syipmong/yeep-prolag/issues)
- **Documentation**: See included guides and `INSTALLATION.md`
- **Examples**: Check the `examples/` folder
- **Community**: Join the discussion on GitHub

## 🔮 **What's Next**

- Package manager support (Chocolatey, Homebrew, APT)
- Enhanced IDE integrations
- More built-in functions and libraries
- Performance optimizations
- Language server protocol support

---

**Happy coding with Yeep v2.0.1!** 🎉

*Yeep Programming Language - Simple, Modern, Powerful*
