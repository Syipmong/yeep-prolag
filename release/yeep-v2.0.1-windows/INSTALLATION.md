# Yeep Programming Language - Installation Guide

## System-Wide Installation

Yeep v2.0.1 now supports easy system-wide installation that allows you to run `yeep` from anywhere on your system.

## Quick Start

### Windows
```bash
# Download or clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build Yeep
build.bat

# Install system-wide (requires Administrator privileges)
install.bat
```

### Linux/macOS
```bash
# Download or clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build Yeep
./build.sh

# Install system-wide (requires root privileges)
sudo ./install.sh
```

## Detailed Installation

### Prerequisites

**Windows:**
- MinGW-w64 or MSYS2 with GCC
- Windows 10 or later

**Linux/macOS:**
- GCC 7.0+ or Clang 5.0+
- make utility

### Step 1: Build Yeep

Before installation, you need to build the Yeep executable.

**Windows:**
```cmd
build.bat
```

**Linux/macOS:**
```bash
chmod +x build.sh
./build.sh
```

This will create `build/yeep.exe` (Windows) or `build/yeep` (Unix).

### Step 2: Install System-Wide

**Windows (Administrator required):**
```cmd
# Right-click Command Prompt → "Run as Administrator"
install.bat
```

**Linux/macOS (Root required):**
```bash
sudo ./install.sh
```

### Step 3: Verify Installation

After installation, restart your terminal and test:

```bash
yeep --version
yeep --help
```

## Installation Locations

### Windows
- **System-wide (Admin):** `C:\Program Files\Yeep\`
- **User-only:** `%USERPROFILE%\Yeep\`
- **Added to PATH:** Automatically

### Linux/macOS
- **System-wide (Root):** `/usr/local/bin/yeep`
- **User-only:** `~/.local/bin/yeep`
- **Documentation:** `/usr/local/share/doc/yeep/` or `~/.local/share/doc/yeep/`
- **Examples:** `/usr/local/lib/yeep/examples/` or `~/.local/lib/yeep/examples/`

## Usage After Installation

Once installed, you can use Yeep from anywhere:

```bash
# Start interactive REPL
yeep

# Run a script
yeep myscript.yeep

# Show help
yeep --help

# Show version
yeep --version

# Run examples (adjust path for your system)
yeep /usr/local/lib/yeep/examples/hello_working.yeep  # Linux/macOS
yeep "C:\Program Files\Yeep\examples\hello_working.yeep"  # Windows
```

## Uninstalling

### Windows
```cmd
# Run the uninstaller from the installation directory
"C:\Program Files\Yeep\uninstall.bat"
# or
"%USERPROFILE%\Yeep\uninstall.bat"
```

### Linux/macOS
```bash
# System-wide installation
sudo /usr/local/lib/yeep/uninstall.sh

# User installation
~/.local/lib/yeep/uninstall.sh
```

## Alternative Installation Methods

### Manual Installation

If the automatic installation doesn't work:

1. Copy `build/yeep.exe` (or `build/yeep`) to a directory in your PATH
2. Create a folder for examples and documentation
3. Manually add the directory to your system PATH

### Portable Installation

For a portable installation that doesn't modify system PATH:

1. Create a folder anywhere (e.g., `C:\Tools\Yeep` or `~/tools/yeep`)
2. Copy `build/yeep.exe` (or `build/yeep`) to that folder
3. Copy example files and documentation
4. Use the full path to run: `C:\Tools\Yeep\yeep.exe myscript.yeep`

## Troubleshooting

### Windows Issues

**"Access denied" or "Permission denied":**
- Make sure you're running Command Prompt as Administrator
- Try installing to user directory (it will fall back automatically)

**"yeep is not recognized as a command":**
- Restart your command prompt/terminal
- Check that the installation directory is in your PATH
- Try logging out and back in

### Linux/macOS Issues

**"Permission denied":**
- Make sure you're using `sudo` for system-wide installation
- Check that you have write permissions to the target directory

**"yeep: command not found":**
- Run `source ~/.bashrc` or `source ~/.zshrc`
- Restart your terminal
- Check that `~/.local/bin` or `/usr/local/bin` is in your PATH

### Build Issues

**"gcc not found" or "compiler not found":**
- **Windows:** Install MinGW-w64 or MSYS2
- **Linux:** Install build tools: `sudo apt-get install build-essential` (Ubuntu/Debian)
- **macOS:** Install Xcode Command Line Tools: `xcode-select --install`

**Compilation errors:**
- Make sure you have a C++17 compatible compiler
- Check that all source files are present in the `src/` directory

## Support

If you encounter issues with installation:

1. Check the [GitHub Issues](https://github.com/Syipmong/yeep-prolag/issues)
2. Run the diagnostic script: `diagnose.bat` (Windows) or `./diagnose.sh` (Linux/macOS)
3. Create a new issue with your system information and error messages

## Development Installation

For developers who want to modify Yeep:

```bash
# Clone the repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build and test
./build.sh  # or build.bat on Windows

# Run tests
./build/yeep test_simple.yeep

# For active development, don't install system-wide
# Instead, use ./build/yeep directly or create an alias
alias yeep='./build/yeep'  # Linux/macOS
doskey yeep=C:\path\to\yeep-prolag\build\yeep.exe $*  # Windows
```

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
