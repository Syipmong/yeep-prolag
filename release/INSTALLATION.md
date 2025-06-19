# 📦 Yeep v2.0.0 - Installation Guide

**Easy installation for Windows, Linux, and macOS**

## 🚀 Quick Install (Recommended)

### Windows
```powershell
# Download and run the installer
curl -LO https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-v2.0.0-windows.zip
Expand-Archive yeep-v2.0.0-windows.zip
cd yeep-v2.0.0-windows
.\install.bat
```

### Linux/macOS
```bash
# Download and install
curl -LO https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-v2.0.0-linux.tar.gz
tar -xzf yeep-v2.0.0-linux.tar.gz
cd yeep-v2.0.0-linux
sudo ./install.sh
```

## 📋 Manual Installation

### Option 1: Download Pre-built Binaries

1. **Go to releases**: https://github.com/Syipmong/yeep-prolag/releases/latest
2. **Download** your platform:
   - Windows: `yeep-v2.0.0-windows.zip`
   - Linux: `yeep-v2.0.0-linux.tar.gz`
   - macOS: `yeep-v2.0.0-macos.tar.gz`
3. **Extract** the archive
4. **Run installer** (see platform instructions below)

### Option 2: Build from Source

#### Prerequisites
- **C++ Compiler**: GCC/G++ with C++17 support
- **Git**: For cloning the repository

#### Steps
```bash
# Clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build (Windows)
.\build_official.bat

# Build (Linux/macOS)
chmod +x build_official.sh
./build_official.sh
```

## 🖥️ Platform-Specific Instructions

### Windows Installation

#### Method 1: Automated Installer
```powershell
# Download and extract
curl -LO https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-v2.0.0-windows.zip
Expand-Archive yeep-v2.0.0-windows.zip
cd yeep-v2.0.0-windows

# Run installer (creates %USERPROFILE%\bin\yeep.exe)
.\install.bat

# Add to PATH if needed
$env:PATH += ";$env:USERPROFILE\bin"
```

#### Method 2: Manual Setup
```powershell
# Create bin directory
mkdir "$env:USERPROFILE\bin"

# Copy executable
copy yeep.exe "$env:USERPROFILE\bin\yeep.exe"

# Add to PATH permanently
[Environment]::SetEnvironmentVariable("PATH", $env:PATH + ";$env:USERPROFILE\bin", "User")
```

#### Method 3: Chocolatey (Future)
```powershell
# Coming soon!
choco install yeep
```

### Linux Installation

#### Method 1: System-wide Install
```bash
# Extract and install
tar -xzf yeep-v2.0.0-linux.tar.gz
cd yeep-v2.0.0-linux
sudo ./install.sh
```

#### Method 2: User Install
```bash
# Install to user directory
mkdir -p ~/.local/bin
cp yeep ~/.local/bin/yeep
chmod +x ~/.local/bin/yeep

# Add to PATH (add to ~/.bashrc or ~/.zshrc)
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
source ~/.bashrc
```

#### Method 3: Package Managers (Future)
```bash
# Coming soon!
sudo apt install yeep           # Ubuntu/Debian
sudo dnf install yeep           # Fedora
sudo pacman -S yeep             # Arch Linux
```

### macOS Installation

#### Method 1: System Install
```bash
# Extract and install
tar -xzf yeep-v2.0.0-macos.tar.gz
cd yeep-v2.0.0-macos
sudo ./install.sh
```

#### Method 2: User Install
```bash
# Install to user directory
mkdir -p ~/.local/bin
cp yeep ~/.local/bin/yeep
chmod +x ~/.local/bin/yeep

# Add to PATH (add to ~/.zshrc or ~/.bash_profile)
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.zshrc
source ~/.zshrc
```

#### Method 3: Homebrew (Future)
```bash
# Coming soon!
brew install yeep
```

## ✅ Verify Installation

After installation, verify Yeep is working:

```bash
# Check version
yeep --version   # (Coming in v2.1.0)

# Or start interactive mode
yeep

# You should see:
# Yeep Programming Language v2.0.0
# Type 'exit' to quit, 'help' for help
# yeep>
```

## 🏃‍♂️ Quick Start

### Interactive Mode
```bash
yeep
```
```yeep
yeep> print("Hello, World!");
Hello, World!
yeep> help
yeep> exit
```

### Script Execution
```bash
# Create a script file
echo 'print("Welcome to Yeep v2.0.0!");' > hello.yeep

# Run the script
yeep hello.yeep
```

## 🔧 Build Dependencies (For Source Builds)

### Windows
- **MinGW-w64** or **Visual Studio** with C++ support
- **MSYS2** (recommended): https://www.msys2.org/

### Linux
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install g++ make

# Fedora
sudo dnf install gcc-c++ make

# Arch Linux
sudo pacman -S gcc make
```

### macOS
```bash
# Install Xcode Command Line Tools
xcode-select --install

# Or using Homebrew
brew install gcc
```

## 🆘 Troubleshooting

### Common Issues

#### "yeep: command not found"
- **Solution**: Add installation directory to PATH
- **Windows**: Add `%USERPROFILE%\bin` to PATH
- **Linux/macOS**: Add `~/.local/bin` to PATH

#### "Permission denied" (Linux/macOS)
```bash
# Make executable
chmod +x yeep

# Or run with sudo for system install
sudo ./install.sh
```

#### Build errors
- **Ensure C++17 support**: GCC 7+ or equivalent
- **Check compiler**: `g++ --version`
- **Update compiler** if needed

### Get Help
- **GitHub Issues**: https://github.com/Syipmong/yeep-prolag/issues
- **Documentation**: https://github.com/Syipmong/yeep-prolag/wiki
- **Community**: GitHub Discussions

## 🎯 Next Steps

After installation:
1. **Try the demo**: `yeep demo_v2.yeep`
2. **Read documentation**: Check the wiki
3. **Join community**: Star the repository
4. **Stay updated**: Watch for v2.1.0 with variables!

---

**Yeep v2.0.0 - Ready for production use!** 🚀
