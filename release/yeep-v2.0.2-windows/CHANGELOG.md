# Yeep Programming Language - Changelog

## Version 2.0.0 - "C++ Migration" (2025-06-19)

### 🎉 Major Release - Complete C++ Rewrite

#### ✨ **New Features**
- **Complete C++ migration** from legacy C codebase
- **Interactive REPL** with help, version, and exit commands
- **Script file execution** for .yeep files
- **Print statements** with string literals: `print("text");`
- **Professional build system** with automated compilation

#### 🏗️ **Architecture Changes**
- **Modern C++17** codebase with smart pointers
- **Exception handling** throughout the system
- **Type-safe tokens** using std::variant
- **RAII memory management** - no manual allocation/deallocation
- **Modular design** with clear separation of concerns

#### 🛠️ **Technical Improvements**
- **Lexical analysis** - Complete tokenization system
- **Error handling** - Graceful error reporting and recovery
- **Build automation** - Official build script (build_official.bat)
- **Documentation** - Comprehensive README and guides

#### 🔧 **Developer Experience**
- **VS Code extension** published and integrated
- **GitHub Linguist** support for .yeep files
- **Professional documentation** with wiki
- **Clean, maintainable** codebase

#### 💾 **Files Added/Modified**
- `src/main.cpp` - New C++ entry point
- `src/core/YeepEngine.cpp` - Main interpreter engine
- `src/core/Token.cpp` - Modern token implementation
- `src/core/Lexer.cpp` - C++ lexical analyzer
- `include/yeep.hpp` - Main header with engine class
- `include/core/*.hpp` - Core component headers
- `build_official.bat` - Official build script
- `demo.yeep` - Working demonstration script

#### 🎯 **Breaking Changes**
- **Requires C++ compiler** (G++/MinGW)
- **New build process** (run build_official.bat)
- **Different executable** (build/yeep.exe)

---

## Version 1.x Series - Legacy C Implementation

### Version 1.2.0 and earlier
- Original C implementation
- Basic interpreter functionality
- Legacy architecture
- Manual memory management

---

## Upcoming Releases (Planned)

### Version 2.1.0 - "Variables & Expressions" (Planned)
- Variable declarations: `let x = 42;`
- Variable usage in print: `print(x);`
- Basic arithmetic: `let sum = 5 + 3;`
- Expression evaluation

### Version 2.2.0 - "Control Flow" (Planned)
- Conditional statements: `if (condition) { ... }`
- Boolean expressions and operators
- Comparison operators
- Logical operators (&&, ||, !)

### Version 2.3.0 - "Loops & Functions" (Planned)
- While loops: `while (condition) { ... }`
- Function definitions: `fun name(params) { ... }`
- Function calls with parameters
- Return statements

### Version 2.4.0 - "Enhanced Features" (Planned)
- For loops
- Advanced REPL features
- Debugging capabilities
- Performance optimizations

### Version 2.5.0 - "Standard Library" (Planned)
- Built-in functions
- File I/O operations
- String manipulation
- Math functions

---

## Version History Summary

| Version | Release Date | Type | Description |
|---------|--------------|------|-------------|
| 2.0.0 | 2025-06-19 | 🎉 Major | Complete C++ migration, working interpreter |
| 1.2.0 | - | Legacy | Last C-based version |
| 1.x.x | - | Legacy | Original C implementation |

---

*This changelog follows [Semantic Versioning](https://semver.org/) principles*

**Legend:**
- 🎉 Major release (breaking changes)
- ✨ Minor release (new features)
- 🐛 Patch release (bug fixes)
- 🔧 Development/internal changes
