# 🎉 Yeep v2.0.0 - Complete Installation & User Guide

## 🚀 Choose Your Installation Method

### ⚡ Super Quick (30 seconds)

**For Linux/macOS:**
```bash
curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.sh | bash
```

**For Windows:**
```powershell
iwr -useb https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.ps1 | iex
```

### 📦 Package Managers

| Platform | Command | Auto-Updates |
|----------|---------|--------------|
| 🍎 **macOS/Linux** | `brew tap syipmong/yeep && brew install yeep` | ✅ Yes |
| 🪟 **Windows** | `choco install yeep` | ✅ Yes |
| 🐳 **Docker** | `docker run -it --rm syipmong/yeep:latest` | ✅ Yes |

### 📥 Manual Download

1. **Download** from [GitHub Releases](https://github.com/Syipmong/yeep-prolag/releases/latest)
2. **Choose** your platform:
   - Windows: `yeep-windows-x64.zip`
   - Linux: `yeep-linux-x64.tar.gz`
   - macOS: `yeep-macos-x64.tar.gz`
3. **Extract** and run the installer

## 🎯 Quick Start

After installation:

```bash
# Check installation
yeep --version

# Interactive programming
yeep

# Run a script
echo 'print("Hello, Yeep!");' > hello.yeep
yeep hello.yeep
```

## 📋 What Works Right Now

✅ **Interactive REPL** - Type and run code immediately  
✅ **Script Execution** - Run .yeep files  
✅ **Print Statements** - Output text to console  
✅ **Cross-Platform** - Windows, Linux, macOS  
✅ **Easy Installation** - Multiple installation methods  
✅ **Professional Build** - Modern C++17 architecture  

## 🌟 Example Programs

### Hello World
```yeep
print("Hello, World!");
```

### Multiple Lines
```yeep
print("Welcome to Yeep!");
print("This is version 2.0.0");
print("Built with modern C++");
```

### Interactive Session
```bash
$ yeep
Yeep Programming Language v2.0.0
Interactive interpreter ready!

yeep> print("Interactive programming!");
Interactive programming!

yeep> print("So easy!");
So easy!

yeep> exit
Goodbye!
```

## 🔧 Command Reference

| Command | Description |
|---------|-------------|
| `yeep` | Start interactive REPL |
| `yeep script.yeep` | Run a script file |
| `yeep --version` | Show version number |
| `yeep --help` | Show help information |

## 🆘 Need Help?

### Common Issues

**"Command not found: yeep"**
- Add to PATH: See [troubleshooting guide](https://github.com/Syipmong/yeep-prolag/blob/main/docs/generated/TROUBLESHOOTING.md)

**Installation failed**
- Try different method or check [installation guide](https://github.com/Syipmong/yeep-prolag/blob/main/INSTALLATION.md)

### Get Support

- 🐛 **Bug Reports**: [GitHub Issues](https://github.com/Syipmong/yeep-prolag/issues)
- 💬 **Questions**: [GitHub Discussions](https://github.com/Syipmong/yeep-prolag/discussions)
- 📖 **Documentation**: [Full README](https://github.com/Syipmong/yeep-prolag/blob/main/README.md)

## 🚀 What's Coming Next

Yeep v2.0.0 is the stable foundation. Future versions will add:

- **Variables and expressions** (`x = 5`)
- **Control flow** (`if`, `while`, `for`)
- **Functions** (`def myFunction()`)
- **Data types** (numbers, booleans, arrays)
- **File operations** (read/write files)
- **Standard library** (math, string utilities)

## 💝 Contributing

Love Yeep? Here's how to help:

- ⭐ **Star** the repository
- 🐛 **Report** bugs you find
- 💡 **Suggest** new features
- 🤝 **Contribute** code improvements
- 📖 **Improve** documentation
- 🗣️ **Tell** others about Yeep

---

## 🎊 Ready to Start?

Choose an installation method above and start programming with Yeep in seconds!

**Yeep v2.0.0 - Making programming accessible, one line at a time** ❤️

*Built with ❤️ by the Yeep community*
