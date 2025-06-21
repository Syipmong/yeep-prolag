# Yeep Programming Language v2.0.1 🎉

**Major Release: System-Wide Installation**

Yeep v2.0.1 introduces professional system-wide installation capabilities, allowing users to install Yeep once and use it from anywhere on their system. This release includes a modernized build system, colorized REPL, and comprehensive documentation.

## 🚀 **Key Features**

### ✨ **System-Wide Installation**
- **Windows**: Smart admin/user detection with automatic PATH management
- **Linux/macOS**: Standard Unix installation with shell integration
- **One-Command Install**: Simple `install.bat` or `sudo ./install.sh`
- **Clean Uninstall**: Automatic uninstaller generation

### 🎨 **Professional REPL**
- **Colorized Output**: Beautiful ANSI colors and formatting
- **Built-in Commands**: `help`, `version`, `clear`, `examples`
- **Smart Features**: Auto-semicolon, error recovery, cross-platform

### 📦 **Complete Package**
- **Ready-to-Use**: Pre-built executable included
- **Full Documentation**: Installation guides, language spec, examples
- **VSCode Extension**: Professional syntax highlighting
- **29+ Examples**: Sample programs to get started

## 📥 **Installation**

### Quick Install

**Windows:**
```cmd
# Extract ZIP file, then run as Administrator:
install.bat
```

**Linux/macOS:**
```bash
# Extract archive, then:
sudo ./install.sh    # System-wide
# OR
./install.sh         # User-only
```

### Verification
```bash
yeep --version       # Should show v2.0.1
yeep --help         # Show usage information
yeep                # Start interactive REPL
```

## 📋 **What's Included**

- ✅ **yeep.exe** - Main executable (Windows)
- ✅ **install.bat/install.sh** - Cross-platform installers
- ✅ **Complete documentation** - README, installation guide, language spec
- ✅ **29+ example programs** - Learn by example
- ✅ **Source code** - Full C++ implementation
- ✅ **VSCode extension** - Professional development environment
- ✅ **Build scripts** - Compile from source
- ✅ **Test utilities** - Installation testing tools

## 🆕 **New in v2.0.1**

### System Integration
- System-wide installation with PATH management
- Professional installer/uninstaller scripts
- Cross-platform compatibility (Windows, Linux, macOS)
- Smart privilege detection and fallback

### User Experience
- Colorized REPL with built-in commands
- Professional welcome screen and help system
- Enhanced error handling and recovery
- Consistent cross-platform behavior

### Developer Experience
- Clean, modern C++17 codebase
- Streamlined build system
- Comprehensive documentation
- Professional VSCode extension

## 🔧 **Technical Details**

- **Languages**: C++17
- **Platforms**: Windows 10+, Linux, macOS 10.14+
- **Dependencies**: GCC 7.0+ or Clang 5.0+
- **Package Size**: ~390KB
- **Memory Usage**: <5MB typical

## 🐛 **Bug Fixes**

- Fixed build system issues with deprecated scripts
- Resolved Windows PATH management problems
- Improved REPL error handling and recovery
- Enhanced cross-platform compatibility
- Cleaned up compiler warnings

## 📖 **Documentation**

- `README.md` - Main documentation
- `INSTALLATION.md` - Complete installation guide
- `QUICK-START.md` - Get started in 5 minutes
- `LANGUAGE_SPEC.md` - Language reference
- `USER_GUIDE.md` - Usage guide with examples

## 🔄 **Upgrading**

From any previous version:
1. Uninstall old version (if any)
2. Download and extract v2.0.1
3. Run installer
4. Restart terminal/command prompt
5. Verify: `yeep --version`

## 💡 **Usage Examples**

```bash
# Interactive REPL
yeep

# Run a script
yeep examples/hello_working.yeep

# Try the calculator example
yeep examples/calculator_example.yeep

# Explore built-in help
yeep
> help
> examples
> version
```

## 🔮 **Coming Next**

- Package manager integration (Chocolatey, Homebrew)
- Language server protocol support
- Enhanced built-in functions
- Performance optimizations
- IDE integrations

---

## 📥 **Downloads**

| Platform | File | Size | SHA256 |
|----------|------|------|--------|
| Windows x64 | `yeep-v2.0.1-windows-x64.zip` | 390KB | See `.sha256` file |

**System Requirements:**
- Windows 10+ with MinGW-w64 or MSYS2
- Linux with GCC 7.0+ or Clang 5.0+
- macOS 10.14+ with Xcode Command Line Tools

**Installation:** Extract and run `install.bat` (Windows) or `sudo ./install.sh` (Linux/macOS)

---

**🎉 Ready to code with Yeep v2.0.1!**

For issues, questions, or contributions, please visit the GitHub repository.
