# Troubleshooting Guide 🛠️

Complete guide to solving common Yeep installation and usage issues.

---

## 🚨 Installation Issues

### Windows Installation Problems

#### ❌ **"Download was unexpected at this time" Error**

**Problem:** Batch file syntax error preventing installer from running.

**Solution:**
```cmd
# Download latest release (v1.0.6 or newer)
# This issue is fixed in recent versions

# Alternative: Use simple installer
install-simple.bat

# Or use debug installer for detailed output
install-debug.bat
```

**Why it happens:** Older versions had complex batch syntax that caused parsing errors.

---

#### ❌ **"C:\Program Files\Yeep is empty" Error**

**Problem:** Installation directory created but no files copied.

**Solutions:**

1. **Run as Administrator:**
   ```cmd
   # Right-click install.bat → "Run as administrator"
   install.bat
   ```

2. **Check for permission fallback:**
   ```cmd
   # Installer should automatically fall back to user directory
   # Check: C:\Users\YourName\Yeep\
   dir "C:\Users\%USERNAME%\Yeep"
   ```

3. **Use alternative installer:**
   ```cmd
   install-simple.bat
   ```

**Why it happens:** Permission issues or installer logic problems in older versions.

---

#### ❌ **"Failed to create user directory" Error**

**Problem:** Cannot create installation directory even in user folder.

**Diagnostic Steps:**
```cmd
# Check if directory already exists
dir "C:\Users\%USERNAME%\Yeep"

# Check disk space
dir C:\

# Try manual creation
mkdir "C:\Users\%USERNAME%\YeepTest"
```

**Solutions:**
1. **Clear existing directory:**
   ```cmd
   rmdir /s "C:\Users\%USERNAME%\Yeep"
   install.bat
   ```

2. **Check antivirus software** - may be blocking directory creation

3. **Run from different location** - some locations have restricted access

---

#### ❌ **"msys-2.0.dll was not found" Error**

**Problem:** Missing DLL dependency (older versions only).

**Solution:**
```cmd
# Download latest release (v1.0.1 or newer)
# Static linking eliminates this issue
```

**Why it happens:** Older builds were dynamically linked to MSYS2 libraries.

---

#### ❌ **"build.bat is not recognized" Error**

**Problem:** Downloaded source code instead of release.

**Solution:**
1. Go to [**Releases**](https://github.com/Syipmong/yeep-prolag/releases/latest)
2. Download `yeep-windows-x64.zip` (NOT source code)
3. Extract ALL files from ZIP
4. Verify `yeep.exe` exists in folder
5. Run `install.bat` as administrator

---

#### ❌ **"Access is denied" Errors**

**Problem:** Insufficient permissions for installation.

**Solutions:**

1. **Run as Administrator:**
   ```cmd
   # Right-click Command Prompt → "Run as administrator"
   cd C:\path\to\yeep-windows-x64
   install.bat
   ```

2. **Install to user directory manually:**
   ```cmd
   mkdir "%USERPROFILE%\Yeep"
   copy yeep.exe "%USERPROFILE%\Yeep\"
   copy *.md "%USERPROFILE%\Yeep\"
   ```

3. **Check Windows User Account Control (UAC)** settings

---

### Linux/macOS Installation Problems

#### ❌ **"Permission denied" Error**

**Problem:** Cannot write to system directories.

**Solutions:**

1. **Use sudo for system-wide install:**
   ```bash
   sudo ./install.sh
   ```

2. **Install for current user only:**
   ```bash
   # Modify install.sh to use ~/.local/bin
   mkdir -p ~/.local/bin
   cp yeep ~/.local/bin/
   export PATH="$PATH:$HOME/.local/bin"
   ```

3. **Check file permissions:**
   ```bash
   chmod +x install.sh
   chmod +x yeep
   ```

---

#### ❌ **"Command not found: yeep" Error**

**Problem:** Yeep not in system PATH.

**Solutions:**

1. **Check installation location:**
   ```bash
   which yeep
   ls -la /usr/local/bin/yeep
   ```

2. **Add to PATH manually:**
   ```bash
   # Add to ~/.bashrc or ~/.zshrc
   export PATH="$PATH:/usr/local/bin"
   source ~/.bashrc
   ```

3. **Use full path:**
   ```bash
   /usr/local/bin/yeep --version
   ```

---

#### ❌ **"No such file or directory" Error**

**Problem:** Missing dependencies or incorrect architecture.

**Solutions:**

1. **Check architecture:**
   ```bash
   uname -m  # Should be x86_64 for x64 builds
   file yeep  # Check if binary matches your system
   ```

2. **Install dependencies:**
   ```bash
   # Ubuntu/Debian
   sudo apt update
   sudo apt install libc6

   # CentOS/RHEL
   sudo yum install glibc

   # macOS
   # Usually no additional dependencies needed
   ```

---

## 🐛 Runtime Issues

### Execution Problems

#### ❌ **"Undefined variable" Error**

**Problem:** Using variable before declaration.

**Example:**
```yeep
print(x);      // ERROR: x not defined
let x = 10;
```

**Solution:**
```yeep
let x = 10;    // Declare first
print(x);      // Then use
```

---

#### ❌ **"Expected ';'" Syntax Error**

**Problem:** Missing semicolon after statement.

**Example:**
```yeep
let x = 10     // ERROR: Missing semicolon
print(x);
```

**Solution:**
```yeep
let x = 10;    // Add semicolon
print(x);
```

---

#### ❌ **"Unexpected token" Error**

**Problem:** Invalid syntax or typo.

**Common causes:**
```yeep
// Unmatched parentheses
print("Hello"  // ERROR: Missing )

// Invalid identifiers
let 1name = "test";  // ERROR: Cannot start with digit

// Wrong operators
let x = 5 === 5;     // ERROR: Use == not ===
```

**Solutions:**
```yeep
// Fixed versions
print("Hello");      // Matched parentheses
let name1 = "test";  // Valid identifier
let x = 5 == 5;      // Correct operator
```

---

#### ❌ **"Wrong number of arguments" Error**

**Problem:** Function called with incorrect argument count.

**Example:**
```yeep
fun add(a, b) {
    return a + b;
}

add(1, 2, 3);  // ERROR: Expected 2 arguments, got 3
```

**Solution:**
```yeep
add(1, 2);     // Correct number of arguments
```

---

### Performance Issues

#### ⚠️ **Slow recursive functions**

**Problem:** Deep recursion causing performance issues.

**Example:**
```yeep
fun fibonacci(n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);  // Very slow for large n
}
```

**Solution:** Use iterative approach:
```yeep
fun fibonacciIterative(n) {
    if (n <= 1) return n;
    
    let a = 0;
    let b = 1;
    let i = 2;
    
    while (i <= n) {
        let temp = a + b;
        a = b;
        b = temp;
        i = i + 1;
    }
    
    return b;
}
```

---

#### ⚠️ **Infinite loops**

**Problem:** Loop condition never becomes false.

**Example:**
```yeep
let i = 0;
while (i < 10) {
    print(i);
    // ERROR: i never incremented
}
```

**Solution:**
```yeep
let i = 0;
while (i < 10) {
    print(i);
    i = i + 1;  // Make sure to update loop variable
}
```

---

## 💻 Environment Issues

### PATH Problems

#### ❌ **"yeep: command not found" after installation**

**Problem:** PATH not updated correctly.

**Diagnostic:**
```bash
# Check if yeep is in PATH
echo $PATH

# Check installation location
ls /usr/local/bin/yeep        # Linux/macOS
dir "C:\Program Files\Yeep"   # Windows
```

**Solutions:**

**Windows:**
```cmd
# Add to PATH manually
setx PATH "%PATH%;C:\Program Files\Yeep"

# Or use full path
"C:\Program Files\Yeep\yeep.exe" --version
```

**Linux/macOS:**
```bash
# Add to shell profile
echo 'export PATH="$PATH:/usr/local/bin"' >> ~/.bashrc
source ~/.bashrc

# Or use full path
/usr/local/bin/yeep --version
```

---

### File Association Issues

#### ❌ **".yeep files not recognized"**

**Problem:** System doesn't know how to handle .yeep files.

**Solutions:**

**Windows:**
```cmd
# Associate .yeep files with yeep.exe
assoc .yeep=YeepFile
ftype YeepFile="C:\Program Files\Yeep\yeep.exe" "%1"
```

**Linux:**
```bash
# Add shebang to Yeep scripts
#!/usr/bin/env yeep

# Make executable
chmod +x script.yeep
./script.yeep
```

---

## 🔧 Development Issues

### Building from Source

#### ❌ **"gcc: command not found"**

**Problem:** Compiler not installed.

**Solutions:**

**Windows:**
```cmd
# Install MSYS2 or MinGW-w64
# Download from: https://www.msys2.org/
```

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential
```

**CentOS/RHEL:**
```bash
sudo yum groupinstall "Development Tools"
```

**macOS:**
```bash
# Install Xcode Command Line Tools
xcode-select --install
```

---

#### ❌ **"make: command not found"**

**Problem:** Make utility not installed.

**Solutions:**

**Windows (MSYS2):**
```bash
pacman -S make
```

**Linux:**
```bash
# Usually included with build-essential
sudo apt install make
```

**macOS:**
```bash
# Included with Xcode Command Line Tools
xcode-select --install
```

---

### Compilation Errors

#### ❌ **"fatal error: stdio.h: No such file or directory"**

**Problem:** Standard C headers not found.

**Solution:**
```bash
# Install development headers
sudo apt install libc6-dev     # Ubuntu/Debian
sudo yum install glibc-devel   # CentOS/RHEL
```

---

## 🆘 Getting Help

### Diagnostic Information

When reporting issues, include:

1. **Version information:**
   ```bash
   yeep --version
   ```

2. **System information:**
   ```bash
   # Windows
   systeminfo | findstr /B /C:"OS Name" /C:"OS Version"

   # Linux
   uname -a
   cat /etc/os-release

   # macOS
   sw_vers
   ```

3. **Error messages:** Copy the exact error text

4. **Steps to reproduce:** Detailed steps that cause the issue

---

### Self-Diagnosis Script

Create `diagnose.yeep` to test your installation:

```yeep
// Yeep Installation Test
print("=== Yeep Installation Diagnostic ===");

// Test basic functionality
print("✅ Basic print works");

// Test variables
let testVar = 42;
print("✅ Variable assignment: " + testVar);

// Test arithmetic
let result = 5 + 3;
print("✅ Arithmetic: 5 + 3 = " + result);

// Test functions
fun testFunction(x) {
    return x * 2;
}
print("✅ Function call: testFunction(5) = " + testFunction(5));

// Test control flow
if (true) {
    print("✅ If statements work");
}

let i = 0;
while (i < 3) {
    i = i + 1;
}
print("✅ While loops: counted to " + i);

print("=== All tests passed! ===");
```

Run with:
```bash
yeep diagnose.yeep
```

---

### Support Channels

1. **GitHub Issues:** [Report bugs and problems](https://github.com/Syipmong/yeep-prolag/issues)

2. **Discussions:** [Ask questions and get help](https://github.com/Syipmong/yeep-prolag/discussions)

3. **Wiki:** [Check other documentation pages](Home)

4. **Email:** Contact the maintainer for complex issues

---

### Quick Reference

**Most Common Solutions:**
1. Run installer as administrator (Windows)
2. Download release, not source code
3. Check PATH configuration
4. Use alternative installers (`install-simple.bat`)
5. Verify all files extracted from ZIP

**Before Reporting Issues:**
1. Try latest release version
2. Check this troubleshooting guide
3. Run diagnostic script
4. Search existing GitHub issues

---

**Need more help?** Check out:
- [**Installation Guide**](Installation-Guide) - Detailed setup instructions
- [**FAQ**](FAQ) - Frequently asked questions
- [**Language Tutorial**](Language-Tutorial) - Learn Yeep basics
