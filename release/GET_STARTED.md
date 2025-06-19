# 🎉 Welcome to Yeep Programming Language v2.0.0!

**The easiest way to get started with modern programming**

[![Version](https://img.shields.io/badge/Version-2.0.0-brightgreen?style=for-the-badge)](https://github.com/Syipmong/yeep-prolag/releases/latest)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue?style=for-the-badge)](https://github.com/Syipmong/yeep-prolag/blob/main/INSTALLATION.md)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)](https://github.com/Syipmong/yeep-prolag/blob/main/LICENSE)

## 🚀 Quick Start (60 seconds!)

### Option 1: One-Line Installation ⚡

**Linux/macOS:**
```bash
curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.sh | bash
```

**Windows (PowerShell):**
```powershell
iwr -useb https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.ps1 | iex
```

### Option 2: Package Managers 📦

**Homebrew (macOS/Linux):**
```bash
brew tap syipmong/yeep && brew install yeep
```

**Chocolatey (Windows):**
```powershell
choco install yeep
```

**Docker:**
```bash
docker run -it --rm syipmong/yeep:latest
```

### Option 3: Manual Download 📥

1. Go to [Releases](https://github.com/Syipmong/yeep-prolag/releases/latest)
2. Download for your platform:
   - 🪟 Windows: `yeep-windows-x64.zip`
   - 🐧 Linux: `yeep-linux-x64.tar.gz`
   - 🍎 macOS: `yeep-macos-x64.tar.gz`
3. Extract and run the installer

## 🎯 Your First Yeep Program

After installation, try this:

```bash
# Start the interactive REPL
yeep

# Or create a script file
echo 'print("Hello, Yeep v2.0.0!");' > hello.yeep
yeep hello.yeep
```

## 📖 What You Can Do

### Interactive Programming
```bash
$ yeep
Yeep Programming Language v2.0.0
Interactive interpreter ready!

yeep> print("Welcome to programming!");
Welcome to programming!

yeep> print("This is so easy!");
This is so easy!
```

### Script Execution
Create `my-script.yeep`:
```yeep
print("Starting my program...");
print("Yeep makes programming fun!");
print("Done!");
```

Run it:
```bash
yeep my-script.yeep
```

### Command Line Tools
```bash
yeep --version          # Check version
yeep --help             # Get help
yeep script.yeep        # Run a script
yeep                    # Start REPL
```

## 🌟 Why Choose Yeep?

- ✅ **Easy to learn** - Simple, clean syntax
- ✅ **Fast setup** - Install in under 60 seconds
- ✅ **Cross-platform** - Works on Windows, Linux, macOS
- ✅ **Interactive** - Built-in REPL for experimentation
- ✅ **Modern** - Written in C++17 with best practices
- ✅ **Lightweight** - Small footprint, fast execution
- ✅ **Professional** - Proper build system and packaging

## 📚 Learn More

| Resource | Description |
|----------|-------------|
| 📖 [Full Documentation](https://github.com/Syipmong/yeep-prolag/blob/main/README.md) | Complete language guide |
| 🛠️ [Installation Guide](https://github.com/Syipmong/yeep-prolag/blob/main/INSTALLATION.md) | Detailed setup instructions |
| 📋 [Changelog](https://github.com/Syipmong/yeep-prolag/blob/main/CHANGELOG.md) | What's new in each version |
| 🔧 [Troubleshooting](https://github.com/Syipmong/yeep-prolag/blob/main/docs/generated/TROUBLESHOOTING.md) | Common issues and solutions |
| 🎯 [Examples](https://github.com/Syipmong/yeep-prolag/blob/main/examples/) | Sample programs |

## 🤝 Community & Support

- 🐛 **Found a bug?** [Report it](https://github.com/Syipmong/yeep-prolag/issues)
- 💡 **Have an idea?** [Share it](https://github.com/Syipmong/yeep-prolag/discussions)
- ⭐ **Like Yeep?** Star the repository!
- 🤝 **Want to contribute?** Check our [contributing guide](https://github.com/Syipmong/yeep-prolag/blob/main/CONTRIBUTING.md)

## 🔄 Staying Updated

```bash
# Check your version
yeep --version

# Update via package manager
brew upgrade yeep          # Homebrew
choco upgrade yeep         # Chocolatey

# Or reinstall with one-liner
curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.sh | bash
```

## 🎊 Next Steps

1. ✅ **Install Yeep** (you're here!)
2. 🎯 **Try the examples** above
3. 📖 **Read the docs** for advanced features
4. 🌟 **Build something awesome**
5. 🤝 **Share with the community**

---

**Ready to start programming with Yeep?** Choose your installation method above and get started in seconds! 🚀

*Yeep v2.0.0 - Making programming accessible to everyone* ❤️
