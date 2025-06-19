# Installation Guide 🛠️

This guide covers installing Yeep on Windows, Linux, and macOS using pre-built releases or building from source.

---

## 📥 Quick Install (Recommended)

### 🪟 **Windows**

#### Method 1: Download Release (Recommended)
1. **Download** the latest release:
   - Go to [**Releases**](https://github.com/Syipmong/yeep-prolag/releases/latest)
   - Download `yeep-windows-x64.zip`

2. **Extract** the ZIP file completely to a folder

3. **Install** as administrator:
   ```cmd
   # Right-click "install.bat" → "Run as administrator"
   install.bat
   ```

4. **Verify** installation:
   ```cmd
   yeep --version
   ```

#### Method 2: Alternative Installers
If the main installer has issues:
```cmd
# Simple installer (minimal output)
install-simple.bat

# Debug installer (detailed output)
install-debug.bat
```

---

### 🐧 **Linux**

#### Method 1: One-Line Install
```bash
curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-quick.sh | bash
```

#### Method 2: Manual Install
1. **Download** and extract:
   ```bash
   wget https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-linux-x64.tar.gz
   tar -xzf yeep-linux-x64.tar.gz
   cd yeep-linux-x64
   ```

2. **Install**:
   ```bash
   # Install for current user
   chmod +x install.sh
   ./install.sh
   
   # OR install system-wide
   sudo ./install.sh
   ```

3. **Verify**:
   ```bash
   yeep --version
   ```

---

### 🍎 **macOS**

#### Method 1: Download Release
1. **Download** and extract:
   ```bash
   curl -L -o yeep-macos-x64.tar.gz https://github.com/Syipmong/yeep-prolag/releases/latest/download/yeep-macos-x64.tar.gz
   tar -xzf yeep-macos-x64.tar.gz
   cd yeep-macos-x64
   ```

2. **Install**:
   ```bash
   chmod +x install.sh
   sudo ./install.sh
   ```

3. **Verify**:
   ```bash
   yeep --version
   ```

---

## 📍 Installation Locations

### Windows
- **System-wide**: `C:\Program Files\Yeep\`
- **User-only**: `C:\Users\YourName\Yeep\`

### Linux/macOS  
- **System-wide**: `/usr/local/bin/yeep`
- **User-only**: `~/.local/bin/yeep`

---

## 🎯 After Installation

### Test Your Installation
```bash
# Start interactive shell
yeep

# Run example program
yeep examples/hello.yeep

# Show help
yeep --help
```

### Expected Output
```
$ yeep --version
Yeep Programming Language v1.0.8
Copyright (c) 2025 Yipmong Said
Licensed under MIT License

$ yeep examples/hello.yeep
Hello, World!
Welcome to Yeep Programming Language!
```

---

## ⚙️ Environment Setup

### PATH Configuration
The installer automatically adds Yeep to your system PATH. If it doesn't work:

#### Windows
1. Open System Properties → Environment Variables
2. Add `C:\Program Files\Yeep` (or your install path) to PATH
3. Restart command prompt

#### Linux/macOS
Add to your shell profile (`~/.bashrc`, `~/.zshrc`, etc.):
```bash
export PATH="$PATH:/usr/local/bin"
# or for user install:
export PATH="$PATH:$HOME/.local/bin"
```

---

## 🔧 IDE/Editor Setup

### Visual Studio Code
1. Install the "Yeep Language Support" extension (coming soon!)
2. Associate `.yeep` files with the Yeep language

### Vim/Neovim
Add to your `.vimrc`:
```vim
autocmd BufNewFile,BufRead *.yeep set filetype=yeep
```

### Other Editors
Associate `.yeep` files with C-style syntax highlighting as a fallback.

---

## 🧪 Verify Complete Installation

Run this verification script:

```bash
# Create a test file
echo 'let x = 42; print("Test: " + x);' > test.yeep

# Run it
yeep test.yeep

# Expected output: Test: 42
rm test.yeep
```

---

## 🚫 Uninstallation

### Windows
```cmd
# Run the uninstaller from installation directory
"C:\Program Files\Yeep\uninstall.bat"
```

### Linux/macOS
```bash
# If installed system-wide
sudo make uninstall

# Or manually
sudo rm -f /usr/local/bin/yeep
```

---

## ❗ Need Help?

If you encounter issues:
1. Check the [**Troubleshooting Guide**](Troubleshooting)
2. Try alternative installers (`install-simple.bat`, `install-debug.bat`)
3. [**Report an issue**](https://github.com/Syipmong/yeep-prolag/issues)

---

**Next Steps**: 
- 📚 [**Language Tutorial**](Language-Tutorial) - Learn Yeep syntax
- 💡 [**Examples Gallery**](Examples-Gallery) - See Yeep in action
- ❓ [**FAQ**](FAQ) - Common questions answered
