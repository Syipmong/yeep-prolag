# Yeep Programming Language v2.0.3 - Release Notes

**Release Date:** June 22, 2025  
**Version:** 2.0.3  
**Platform:** Windows, Linux, macOS  

## 🚀 What's New in v2.0.3

### 🔧 **Installation Improvements**
- **Fixed PATH handling in install.bat**: Resolved batch script syntax errors that prevented proper PATH updates during installation
- **Enhanced error handling**: Installation scripts now properly redirect error output and handle edge cases
- **Improved cleanup process**: Better removal of old installations and PATH entries

### 🎯 **Stability Enhancements**
- **Consistent version display**: All version strings now correctly show v2.0.3 across REPL, CLI, and documentation
- **Better error reporting**: Improved diagnostic messages during installation and runtime
- **Cross-platform compatibility**: Enhanced support for different Windows configurations

### 📦 **Package Updates**
- **Clean release package**: Properly versioned distribution files
- **Updated documentation**: All installation guides reflect the latest fixes
- **Fresh install support**: New `install-fresh.bat` script for clean installations

## 🔄 **Migration from v2.0.2**

If you have v2.0.2 installed, you can upgrade by:
1. Running the new `install-fresh.bat` to clean up old installation
2. Or manually uninstalling and running the new installer

## 📁 **Installation**

### Windows
```batch
# Download yeep-v2.0.3-windows-x64.zip
# Extract to a folder
# Run install.bat as administrator (for system-wide) or as user
```

### Linux/macOS
```bash
# Download and extract the package
# Run: chmod +x install.sh
# Run: ./install.sh
```

## 🎯 **Usage**

After installation, restart your terminal and use:
```bash
yeep                    # Start interactive REPL
yeep script.yeep        # Run a Yeep script
yeep --version          # Show version info
yeep --help             # Show help
```

## 🔧 **What's Fixed**

### v2.0.3 Fixes:
- ✅ Fixed PATH handling syntax errors in Windows installer
- ✅ Corrected version display consistency across all components
- ✅ Enhanced installation error handling and user feedback
- ✅ Improved cleanup of previous installations

### Previous Fixes (v2.0.1-2.0.2):
- ✅ Modern C++ migration with robust architecture
- ✅ Beautiful colorized REPL with built-in commands
- ✅ Cross-platform system-wide installation
- ✅ Comprehensive error handling and diagnostics
- ✅ VSCode extension with syntax highlighting
- ✅ Complete example suite and documentation

## 📚 **Resources**

- **GitHub Repository**: https://github.com/Syipmong/yeep-prolag
- **Documentation**: See included README.md and INSTALLATION.md
- **Examples**: Check the `examples/` directory for sample Yeep scripts
- **VSCode Extension**: Available in the release package

## 🐛 **Known Issues**

- Minor compiler warnings in unused parameters (cosmetic only)
- Some edge cases in complex nested expressions may need refinement

## 🎉 **What's Next**

- Enhanced language features and built-in functions
- Performance optimizations
- Extended standard library
- Package manager integration
- IDE plugins for other editors

---

**Full Changelog**: [v2.0.2...v2.0.3](https://github.com/Syipmong/yeep-prolag/compare/v2.0.2...v2.0.3)

**Download**: [yeep-v2.0.3-windows-x64.zip](https://github.com/Syipmong/yeep-prolag/releases/download/v2.0.3/yeep-v2.0.3-windows-x64.zip)

---

*The Yeep Programming Language - Simple, Powerful, Modern* 🎯
