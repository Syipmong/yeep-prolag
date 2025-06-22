# Yeep Programming Language - Usage Guide

## 🚀 Running Yeep After Installation

### Command Line Usage

Once installed, you can run Yeep from any command prompt or terminal:

```cmd
# Start interactive shell (REPL)
yeep

# Run a Yeep script file
yeep script.yeep

# Run with command line options
yeep --help       # Show help information
yeep --version    # Show version information
yeep --repl       # Force REPL mode
```

### 📁 Finding Your Installation

**Windows installations are typically located at:**
- **System-wide**: `C:\Program Files\Yeep\`
- **User-only**: `C:\Users\YourName\Yeep\`

**The installation includes:**
- `yeep.exe` - Main executable
- `yeep.bat` - Command wrapper (allows global `yeep` command)
- `examples/` - Example Yeep programs
- `README.md` - Documentation
- `LICENSE` - License information

### 🎯 Example Usage

#### 1. Interactive Shell (REPL)
```cmd
C:\> yeep
Yeep Programming Language v1.0.4
Type 'exit' to quit.
> let x = 42;
> print("Hello, World! " + x);
Hello, World! 42
> exit
```

#### 2. Running Script Files
```cmd
# Run a script
C:\> yeep hello.yeep

# Run example scripts
C:\> yeep "C:\Program Files\Yeep\examples\hello.yeep"
```

#### 3. Creating Your Own Scripts

Create a file `test.yeep`:
```yeep
let name = "Yeep";
let version = 1.0;

print("Welcome to " + name + " v" + version);

if (version >= 1.0) {
    print("This is a stable release!");
}
```

Run it:
```cmd
C:\> yeep test.yeep
Welcome to Yeep v1
This is a stable release!
```

## 🛠️ Troubleshooting

### ❌ Command Not Found
If `yeep` command is not recognized:

1. **Restart your command prompt** - PATH changes require restart
2. **Check PATH manually**:
   ```cmd
   echo %PATH%
   ```
   Look for your Yeep installation directory

3. **Run directly**:
   ```cmd
   "C:\Program Files\Yeep\yeep.exe" --version
   ```

4. **Re-run installation** as administrator

### ❌ Permission Errors
If you get permission errors:
- Run command prompt as administrator
- Or install to user directory instead of system directory

### ❌ Missing Examples
If examples folder is missing:
- Download fresh release from GitHub
- Ensure all files were extracted during installation

## 🗑️ Uninstalling Yeep

### Easy Uninstall
Run the included uninstaller:
```cmd
# Navigate to your Yeep installation directory
cd "C:\Program Files\Yeep"
uninstall.bat
```

### Manual Uninstall
1. **Delete installation folder**:
   - `C:\Program Files\Yeep\` (system-wide)
   - `C:\Users\YourName\Yeep\` (user-only)

2. **Remove from PATH**:
   - Win+R → `sysdm.cpl` → Environment Variables
   - Edit PATH, remove Yeep directory
   - Click OK

3. **Restart command prompt**

### Verify Uninstall
```cmd
yeep --version
# Should show "command not found"
```

## 🎓 Next Steps

1. **Explore Examples**: Check the `examples/` folder in your installation
2. **Read Documentation**: See README.md for language syntax
3. **Write Your First Program**: Create a `.yeep` file and experiment
4. **Join Community**: Report issues or contribute on GitHub

## 📞 Getting Help

- **Documentation**: Check installed README.md
- **Examples**: Run examples in the `examples/` folder
- **Issues**: Report problems on GitHub
- **Community**: Contribute to the project

Happy coding with Yeep! 🎉
