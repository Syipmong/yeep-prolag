# Yeep v2.0.4 Installation Guide

## 🚀 Quick Installation

### Windows

1. **Download** the latest release from GitHub
2. **Extract** the ZIP file to a folder (e.g., `C:\yeep-v2.0.4`)
3. **Run as Administrator** and execute:
   ```cmd
   install.bat
   ```
4. **Restart** your command prompt
5. **Test** the installation:
   ```cmd
   yeep --version
   ```

### Linux/macOS

1. **Download** the latest release from GitHub
2. **Extract** the archive:
   ```bash
   tar -xzf yeep-v2.0.4-linux.tar.gz
   cd yeep-v2.0.4
   ```
3. **Run** the installer:
   ```bash
   sudo ./install.sh
   ```
4. **Test** the installation:
   ```bash
   yeep --version
   ```

## 📦 Installation Methods

### Method 1: System-Wide Installation (Recommended)

**Windows (Administrator required):**
```cmd
# Run as Administrator
install.bat
```

**Linux/macOS (Root/sudo required):**
```bash
sudo ./install.sh
```

**Benefits:**
- ✅ Available to all users
- ✅ Installs to standard system directories
- ✅ Automatically adds to PATH
- ✅ Professional deployment

### Method 2: User Installation

**Windows:**
```cmd
# Run without administrator privileges
install.bat
```

**Linux/macOS:**
```bash
./install.sh
```

**Benefits:**
- ✅ No administrator/root required
- ✅ Installs to user directory
- ✅ Personal installation only

### Method 3: Portable Installation

1. Extract to any folder
2. Add the folder to your PATH manually
3. Run `yeep` from that folder

## 🗂️ Installation Locations

| Platform | System Install | User Install |
|----------|----------------|--------------|
| Windows  | `C:\Program Files\Yeep\` | `%USERPROFILE%\Yeep\` |
| Linux    | `/usr/local/bin/` | `~/.local/bin/` |
| macOS    | `/usr/local/bin/` | `~/.local/bin/` |

## 🎯 What Gets Installed

1. **yeep executable** - The main Yeep interpreter
2. **Documentation** - README, LICENSE, release notes
3. **Examples** - Sample Yeep scripts (*.yeep files)
4. **Uninstaller** - Easy removal script
5. **PATH configuration** - Automatic PATH updates

## ✅ Verification

After installation, verify Yeep is working:

```bash
# Check version
yeep --version

# Start interactive REPL
yeep

# Run the feature showcase
yeep feature_showcase_v2.0.4.yeep

# Test file operations
yeep -c 'writeFile("test.txt", "Hello Yeep!"); print(readFile("test.txt"));'
```

## 🗑️ Uninstallation

### Windows
```cmd
# Run the uninstaller (created during installation)
%ProgramFiles%\Yeep\uninstall.bat

# Or use the dedicated uninstaller
uninstall.bat
```

### Linux/macOS
```bash
# Remove system installation
sudo rm -f /usr/local/bin/yeep
sudo rm -rf /usr/local/lib/yeep

# Remove user installation  
rm -f ~/.local/bin/yeep
rm -rf ~/.local/lib/yeep
```

## 🔧 Troubleshooting

### Windows Issues

**"yeep is not recognized":**
1. Restart command prompt/PowerShell
2. Check PATH: `echo %PATH%`
3. Re-run installer as Administrator

**Permission denied:**
1. Run installer as Administrator
2. Check antivirus software
3. Try user installation instead

### Linux/macOS Issues

**"yeep: command not found":**
1. Source your shell profile: `source ~/.bashrc`
2. Check PATH: `echo $PATH`
3. Re-run installer with sudo

**Permission denied:**
1. Make executable: `chmod +x install.sh`
2. Run with sudo: `sudo ./install.sh`

## 🎨 Advanced Installation

### Custom Installation Directory

**Windows:**
```cmd
set YEEP_INSTALL_DIR=C:\MyTools\Yeep
install.bat
```

**Linux/macOS:**
```bash
export YEEP_INSTALL_DIR=/opt/yeep
sudo ./install.sh
```

### Development Installation

For developers who want to build from source:

```bash
# Clone repository
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag

# Build
./build.sh  # Linux/macOS
build.bat   # Windows

# Install
sudo ./install.sh    # Linux/macOS
install.bat          # Windows (as Administrator)
```

## 🌟 Post-Installation

After successful installation:

1. **Try the REPL:**
   ```bash
   yeep
   ```

2. **Run examples:**
   ```bash
   yeep feature_showcase_v2.0.4.yeep
   ```

3. **Check new v2.0.4 features:**
   ```bash
   yeep
   > features
   ```

4. **Create your first script:**
   ```yeep
   // hello.yeep
   fun greet(name) {
       return "Hello, " + name + "! Welcome to Yeep v2.0.4!";
   }
   
   print(greet("World"));
   writeFile("greeting.txt", greet("File System"));
   print("Greeting saved to file!");
   ```

## 📞 Support

- **Documentation:** README.md, USER_GUIDE.md
- **Examples:** feature_showcase_v2.0.4.yeep
- **Issues:** https://github.com/Syipmong/yeep-prolag/issues
- **REPL Help:** Type `help` in the Yeep REPL

---

**🎉 Welcome to Yeep v2.0.4 - Happy Coding!**
