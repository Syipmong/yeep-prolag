# FAQ - Frequently Asked Questions ❓

Common questions and answers about the Yeep programming language.

---

## 🚀 General Questions

### **What is Yeep?**
Yeep is a simple, interpreted programming language written in C. It features dynamic typing, functions, control flow, logical operators, and an interactive REPL. It's designed for learning programming concepts and rapid prototyping.

### **Who created Yeep?**
Yeep was created by **Yipmong Said**, a student at Baze University Nigeria, as a learning project to explore programming language design and implementation.

### **Is Yeep free to use?**
Yes! Yeep is released under the MIT License, making it free for personal, educational, and commercial use.

### **What platforms does Yeep support?**
Yeep runs on:
- 🪟 **Windows** (x64)
- 🐧 **Linux** (x64) 
- 🍎 **macOS** (x64)

### **How big is Yeep?**
The entire Yeep distribution is very lightweight:
- **Executable**: ~300KB
- **Complete installation**: <5MB including docs and examples

---

## 📥 Installation Questions

### **How do I install Yeep?**
1. Download the latest release from [GitHub Releases](https://github.com/Syipmong/yeep-prolag/releases/latest)
2. Extract the archive
3. Run the installer (`install.bat` on Windows, `install.sh` on Linux/macOS)
4. Verify with `yeep --version`

See the [**Installation Guide**](Installation-Guide) for detailed instructions.

### **Do I need administrator privileges to install Yeep?**
- **Recommended**: Yes, for system-wide installation
- **Alternative**: The installer can fall back to user-directory installation if admin access is unavailable

### **Can I install Yeep without internet?**
Yes! Once you download the release ZIP/tarball, installation is completely offline.

### **How do I uninstall Yeep?**
- **Windows**: Run `uninstall.bat` from the installation directory
- **Linux/macOS**: Run `sudo make uninstall` or manually delete the files

### **Why does the installer create two directories?**
The installer tries `C:\Program Files\Yeep` first (system-wide), then falls back to `C:\Users\YourName\Yeep` (user-only) if permissions are insufficient.

---

## 💻 Language Questions

### **What programming paradigm does Yeep follow?**
Yeep is primarily **procedural** with some **functional** elements. It supports:
- Variables and expressions
- Functions with return values
- Control flow (if/else, while loops)
- Dynamic typing

### **What data types does Yeep support?**
Currently three main types:
- **Numbers** (integers and floating-point)
- **Strings** (text in double quotes)
- **Booleans** (true/false)

### **Does Yeep have arrays or objects?**
Not yet. Current limitations include:
- No arrays or lists
- No objects or structs
- No hash tables/dictionaries

These may be added in future versions.

### **How do I read user input in Yeep?**
Currently, Yeep doesn't have built-in input functions. You can:
- Use the interactive REPL for testing
- Pass data through variables in scripts
- Future versions may add input capabilities

### **Can I create classes in Yeep?**
No, Yeep doesn't support object-oriented programming yet. It focuses on procedural and functional programming concepts.

### **Does Yeep support file operations?**
Not currently. File I/O may be added in future versions.

---

## 🔧 Usage Questions

### **How do I run a Yeep script?**
```bash
# Save your code in a .yeep file
echo 'print("Hello, World!");' > hello.yeep

# Run it
yeep hello.yeep
```

### **Can I make executable Yeep scripts?**
Yes, on Linux/macOS using shebang:
```yeep
#!/usr/bin/env yeep
print("This is an executable script!");
```
Then: `chmod +x script.yeep && ./script.yeep`

### **How do I use the interactive shell (REPL)?**
```bash
$ yeep
Yeep Programming Language v1.0.8
Type 'exit' to quit, 'help' for help.

yeep> let x = 42;
yeep> print("The answer is " + x);
The answer is 42
yeep> exit
```

### **Can I use Yeep for web development?**
Not directly. Yeep is a general-purpose scripting language without web-specific features. It's better suited for:
- Learning programming concepts
- Mathematical calculations
- Simple automation scripts
- Algorithm prototyping

### **How do I debug Yeep programs?**
Currently debugging is basic:
- Use `print()` statements to trace execution
- Interactive REPL for testing expressions
- Error messages show line numbers for syntax errors

---

## 🏗️ Development Questions

### **Can I contribute to Yeep?**
Absolutely! Contributions are welcome:
- 🐛 [Report bugs](https://github.com/Syipmong/yeep-prolag/issues)
- 💡 [Suggest features](https://github.com/Syipmong/yeep-prolag/issues)
- 🔧 [Submit pull requests](https://github.com/Syipmong/yeep-prolag/pulls)

See the [**Contributing Guide**](Contributing-Guide) for details.

### **Is the source code available?**
Yes! Yeep is fully open source under the MIT License. Source code is available on [GitHub](https://github.com/Syipmong/yeep-prolag).

### **How is Yeep implemented?**
Yeep is written in C and consists of:
- **Lexer** - Tokenizes source code
- **Parser** - Builds abstract syntax tree
- **Interpreter** - Executes the AST
- **REPL** - Interactive shell

### **Can I embed Yeep in my application?**
Currently, Yeep is designed as a standalone interpreter. Embedding capabilities could be added in future versions.

### **How do I build Yeep from source?**
```bash
git clone https://github.com/Syipmong/yeep-prolag.git
cd yeep-prolag
make clean && make
```

See [**Building from Source**](Building-from-Source) for detailed instructions.

---

## 🎯 Learning Questions

### **Is Yeep good for learning programming?**
Yes! Yeep is excellent for learning because:
- Simple, clean syntax
- Interactive REPL for experimentation  
- Clear error messages
- No complex setup required
- Focus on core programming concepts

### **What should I learn before using Yeep?**
Yeep is beginner-friendly. Basic understanding helpful:
- What is a programming language
- Basic command line usage
- Text file editing

### **Are there Yeep tutorials?**
Yes! Check out:
- [**Language Tutorial**](Language-Tutorial) - Step-by-step guide
- [**Examples Gallery**](Examples-Gallery) - Practical examples
- Sample programs in the `examples/` directory

### **How does Yeep compare to other languages?**

| Feature | Yeep | Python | JavaScript |
|---------|------|--------|------------|
| Learning Curve | Easy | Easy | Medium |
| Interactive Shell | ✅ | ✅ | ✅ (Node.js) |
| Dynamic Typing | ✅ | ✅ | ✅ |
| Objects/Classes | ❌ | ✅ | ✅ |
| Arrays | ❌ | ✅ | ✅ |
| File I/O | ❌ | ✅ | ✅ |
| Standard Library | Minimal | Extensive | Extensive |

Yeep is simpler but more limited than Python or JavaScript.

---

## 🚨 Error Questions

### **Why do I get "Download was unexpected at this time"?**
This was a batch file syntax error in older versions. Download the latest release (v1.0.6+) or use `install-simple.bat`.

### **Why is my installation directory empty?**
Usually permission issues. The installer should automatically fall back to your user directory. Check both:
- `C:\Program Files\Yeep\`
- `C:\Users\YourName\Yeep\`

### **Why do I get "command not found: yeep"?**
PATH not configured correctly. Try:
```bash
# Full path
/usr/local/bin/yeep --version
"C:\Program Files\Yeep\yeep.exe" --version

# Or restart your terminal
```

### **Why do I get syntax errors on valid code?**
Check for:
- Missing semicolons `;`
- Unmatched parentheses `()`
- Using reserved keywords as variables
- Typos in operators (`===` instead of `==`)

---

## 🔮 Future Questions

### **What features are planned for future versions?**
Potential future features:
- Arrays and collections
- File I/O operations  
- Module system
- Exception handling
- Standard library expansion
- Performance improvements

See the [**Roadmap**](Roadmap) for more details.

### **When will version 2.0 be released?**
No fixed timeline. Development is community-driven. Major features will be added based on user feedback and contributions.

### **Will Yeep always be free?**
Yes! Yeep will always remain free and open source under the MIT License.

### **Can I request specific features?**
Absolutely! [Open a feature request](https://github.com/Syipmong/yeep-prolag/issues) on GitHub with:
- Description of the feature
- Use cases and examples
- Why it would benefit Yeep users

---

## 📚 Quick Reference

### **Essential Commands**
```bash
yeep --version          # Show version
yeep --help            # Show help
yeep                   # Start REPL
yeep script.yeep       # Run script
```

### **Basic Syntax**
```yeep
let x = 42;            // Variable
print("Hello");        // Output
if (x > 0) { ... }     // Conditional
while (x > 0) { ... }  // Loop
fun name() { ... }     // Function
```

### **Getting Help**
- 📖 [**Language Tutorial**](Language-Tutorial)
- 📋 [**Language Reference**](Language-Reference)
- 🛠️ [**Troubleshooting Guide**](Troubleshooting)
- 💡 [**Examples Gallery**](Examples-Gallery)

---

## ❓ Still Have Questions?

**Can't find your answer here?**

1. 🔍 **Search the wiki** for specific topics
2. 📚 **Check other documentation pages**
3. 🐛 **Search GitHub issues** for similar problems
4. 💬 **Start a discussion** on GitHub
5. 📧 **Contact the maintainer** for complex questions

**We're here to help!** 🤝
