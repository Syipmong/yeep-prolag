# Change Log

All notable changes to the Yeep Programming Language VSCode extension will be documented in this file.

## [2.0.2] - 2025-06-21

### Fixed
- 🔧 **Critical Syntax Fixes**: 
  - Fixed comment syntax from `#` to `//` to match actual Yeep language
  - Updated function keyword from `function` to `fun` to match Yeep v2.0.1 syntax
  - Corrected built-in function names (length, uppercase, get, push, etc.)
  - Fixed all code snippets to use correct syntax
- 📝 **Documentation Updates**:
  - Complete rewrite of README with accurate syntax examples
  - Added comprehensive feature showcase
  - Updated all code samples to use correct Yeep syntax
- 🎨 **Visual Improvements**:
  - Enhanced syntax highlighting for better code readability
  - Improved token recognition for modern Yeep features
  - Better support for array operations and string manipulation

### Changed
- 📚 **Built-in Functions**: Updated to match Yeep v2.0.1 standard library
- 🔤 **Snippets**: All snippets now use correct Yeep syntax (`fun`, `//`, etc.)
- 📖 **Examples**: All example code updated to work with actual Yeep interpreter

## [2.0.1] - 2025-06-21

### Added
- 🎉 **Major Update**: Complete rewrite aligned with Yeep Programming Language v2.0.1
- ✨ **Enhanced Syntax Highlighting**: 
  - Support for all new built-in functions (sqrt, abs, floor, ceil, round, sin, cos, tan, log, pow, random, etc.)
  - Improved keyword recognition (let, and, or, not)
  - Better number and string literal parsing
  - Function call highlighting
  - Punctuation and bracket matching improvements
- 🧠 **IntelliSense Support**:
  - Auto-completion for keywords and built-in functions
  - Hover documentation for built-in functions with examples
  - Context-aware suggestions
- 📝 **Code Snippets**: 15+ new snippets for common patterns:
  - `print` - Print statement
  - `let` - Variable declaration
  - `function` - Function definition
  - `if`/`ifelse` - Conditional statements
  - `while`/`for` - Loop structures
  - `array` - Array declaration
  - `hello` - Hello World template
  - `main` - Main function template
  - Built-in function shortcuts
- ⚡ **Quick Actions**:
  - **F5**: Run current Yeep file
  - **Ctrl+Shift+Y** (Cmd+Shift+Y on Mac): Start Yeep REPL
  - Right-click context menu for running files
  - Command Palette integration
- 🎨 **Improved Language Configuration**:
  - Better auto-closing pairs (including single quotes)
  - Smart indentation rules
  - Code folding support
  - Enhanced bracket matching
- 🔧 **Extension Infrastructure**:
  - Added main extension file with command handlers
  - Hover provider for function documentation  
  - Completion provider for IntelliSense
  - Terminal integration for running code
- 🎯 **Updated Metadata**:
  - New icon and gallery banner
  - Updated categories and keywords
  - Version alignment with Yeep v2.0.1
  - Enhanced description and feature list

### Changed
- 🔄 **Updated Language Grammar**: Complete rewrite of syntax highlighting rules
- 📚 **Improved Documentation**: State-of-the-art README with examples and usage guide
- 🎨 **Enhanced User Experience**: Better color themes and visual indicators
- ⚙️ **Modern VSCode Support**: Updated engine requirement to VSCode 1.74.0+

### Fixed
- 🐛 **String Escaping**: Proper handling of escape sequences in strings
- 🔢 **Number Parsing**: Better recognition of integers vs decimals
- 🎯 **Function Recognition**: Improved function call highlighting
- 📝 **Comment Handling**: More robust comment parsing
- 🔗 **Operator Recognition**: Better logical and comparison operator highlighting

### Technical Details
- 📦 **Package Version**: Updated to 2.0.1 to match language version
- 🎯 **Activation Events**: Optimized extension loading
- 📁 **File Structure**: Reorganized with src/ directory and proper module structure
- 🧪 **Testing**: Added syntax showcase file for development and testing

## [1.0.5] - Previous Release

### Features
- Basic syntax highlighting for Yeep language
- File association for `.yeep` files
- Auto-closing brackets and quotes
- Line comment support with `#`
- Basic language configuration

---

## Development Notes

### Version 2.0.1 Development Process
1. **Analysis**: Studied Yeep v2.0.1 language features and built-in functions
2. **Syntax Grammar**: Completely rewrote TextMate grammar for enhanced highlighting
3. **Features**: Added IntelliSense, snippets, and command support
4. **Documentation**: Created comprehensive README with examples and guides
5. **Testing**: Developed syntax showcase file to validate all features
6. **Integration**: Added hover help and auto-completion
7. **Commands**: Implemented F5 run and REPL integration
8. **Polish**: Updated icons, descriptions, and marketplace metadata

### Future Roadmap
- **Debugging Support**: VSCode debugger integration
- **Error Detection**: Real-time syntax error highlighting  
- **Code Formatting**: Automatic code formatting and beautification
- **Symbol Navigation**: Go to definition, find all references
- **Refactoring**: Variable renaming and code refactoring tools
- **Language Server**: Full Language Server Protocol implementation
- **Testing Framework**: Integrated unit testing support
- **Documentation**: Inline documentation and help system

### Contributing
This extension is part of the Yeep Programming Language project. Contributions are welcome via the main repository at https://github.com/Syipmong/yeep-prolag
