# Contributing Guide 🤝

Welcome to the Yeep community! We're excited to have you contribute to the Yeep programming language.

---

## 🌟 Ways to Contribute

### 🐛 **Bug Reports**
Found a bug? Help us fix it!
- Use clear, descriptive titles
- Include steps to reproduce
- Provide expected vs actual behavior
- Include system information and Yeep version

### 💡 **Feature Requests**  
Have an idea for Yeep? Share it!
- Describe the feature clearly
- Explain the use case and benefits
- Provide examples if possible
- Discuss implementation considerations

### 📚 **Documentation**
Help improve Yeep's documentation:
- Fix typos and grammar
- Add examples and clarifications
- Create tutorials and guides
- Update outdated information

### 💻 **Code Contributions**
Ready to code? Here's how:
- Fix bugs and implement features
- Improve performance
- Add tests
- Enhance error messages

### 💬 **Community Support**
Help other users:
- Answer questions in discussions
- Help with troubleshooting
- Share your Yeep projects
- Write blog posts and tutorials

---

## 🚀 Getting Started

### 1. **Set Up Development Environment**

#### Prerequisites
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install build-essential git

# CentOS/RHEL  
sudo yum groupinstall "Development Tools"
sudo yum install git

# macOS
xcode-select --install
brew install git

# Windows (MSYS2)
pacman -S mingw-w64-x86_64-gcc
pacman -S git
```

#### Clone and Build
```bash
# Fork the repository on GitHub first, then:
git clone https://github.com/YOUR_USERNAME/yeep-prolag.git
cd yeep-prolag

# Build Yeep
make clean && make

# Test the build
./build/yeep --version
./build/yeep examples/hello.yeep
```

### 2. **Understanding the Codebase**

#### Project Structure
```
yeep-prolag/
├── src/           # Source code
│   ├── main.c     # Entry point and CLI
│   ├── lexer.c    # Tokenization
│   ├── parser.c   # Syntax analysis
│   ├── interpreter.c # Execution engine
│   └── shell.c    # REPL implementation
├── include/       # Header files
├── examples/      # Sample programs
├── build/         # Build artifacts
└── tests/         # Test files
```

#### Key Components

**Lexer (`src/lexer.c`)**
- Converts source code into tokens
- Handles keywords, operators, literals
- Manages line numbers for error reporting

**Parser (`src/parser.c`)**
- Builds Abstract Syntax Tree (AST)
- Implements recursive descent parsing
- Handles operator precedence

**Interpreter (`src/interpreter.c`)**
- Executes the AST
- Manages variables and function calls
- Implements built-in functions

**Shell (`src/shell.c`)**
- Interactive REPL
- Command history and editing
- Multi-line input handling

---

## 📝 Contribution Process

### 1. **Choose an Issue**
- Browse [open issues](https://github.com/Syipmong/yeep-prolag/issues)
- Look for `good first issue` labels for beginners
- Comment on the issue to claim it
- Ask questions if anything is unclear

### 2. **Create a Branch**
```bash
# Create feature branch
git checkout -b feature/your-feature-name

# Or for bug fixes
git checkout -b fix/issue-number-description
```

### 3. **Make Changes**
- Write clean, readable code
- Follow existing code style
- Add comments for complex logic
- Update documentation if needed

### 4. **Test Your Changes**
```bash
# Build and test
make clean && make

# Run existing examples
./build/yeep examples/hello.yeep
./build/yeep examples/fibonacci.yeep

# Test REPL
./build/yeep

# Create test cases for new features
echo 'your test code' > test_new_feature.yeep
./build/yeep test_new_feature.yeep
```

### 5. **Commit and Push**
```bash
# Stage changes
git add .

# Commit with descriptive message
git commit -m "feat: add string length function

- Implement strlen() built-in function
- Add tests for string operations
- Update documentation with examples"

# Push to your fork
git push origin feature/your-feature-name
```

### 6. **Create Pull Request**
- Go to GitHub and create a Pull Request
- Use the PR template if available
- Describe your changes clearly
- Link to related issues
- Request review from maintainers

---

## 📋 Coding Standards

### **C Code Style**

#### Naming Conventions
```c
// Functions: camelCase
void parseExpression();
int calculateResult();

// Variables: camelCase
int tokenCount;
char* currentToken;

// Constants: UPPER_SNAKE_CASE
#define MAX_TOKEN_LENGTH 256
#define DEFAULT_STACK_SIZE 1024

// Types: PascalCase
typedef struct Token Token;
typedef enum TokenType TokenType;
```

#### Formatting
```c
// Function definitions
int functionName(int param1, char* param2) {
    // 4-space indentation
    if (condition) {
        doSomething();
    }
    
    return result;
}

// Comments
// Single line for brief explanations
/*
 * Multi-line for detailed
 * explanations
 */
```

#### Error Handling
```c
// Always check for errors
Token* token = malloc(sizeof(Token));
if (token == NULL) {
    fprintf(stderr, "Error: Memory allocation failed\n");
    return NULL;
}

// Use descriptive error messages
if (tokenType != TOKEN_SEMICOLON) {
    reportError("Expected ';' after statement");
    return false;
}
```

### **Documentation Style**

#### Function Documentation
```c
/**
 * Parse an expression from the token stream
 * 
 * @param parser The parser state
 * @param precedence Minimum operator precedence
 * @return AST node for the expression, or NULL on error
 */
ASTNode* parseExpression(Parser* parser, int precedence);
```

#### Code Comments
```c
// Good: Explain why, not what
// Use short-circuit evaluation for performance
if (isNull(node) || node->type != EXPR_BINARY) {
    return false;
}

// Avoid: Redundant comments
// Check if node is null  <-- Bad
if (node == NULL) {
    return false;
}
```

---

## 🧪 Testing Guidelines

### **Manual Testing**
Always test your changes with:

```bash
# Basic functionality
./build/yeep --version
./build/yeep --help

# Example programs
./build/yeep examples/hello.yeep
./build/yeep examples/fibonacci.yeep
./build/yeep examples/factorial.yeep

# Interactive shell
./build/yeep
# Try various expressions and statements

# Error handling
echo 'let x = ;' | ./build/yeep  # Syntax error
echo 'print(undefined);' | ./build/yeep  # Runtime error
```

### **Test Cases**
Create test files for new features:

```yeep
// test_string_length.yeep
let str = "Hello";
let len = strlen(str);
print("Length of '" + str + "' is " + len);
// Expected output: Length of 'Hello' is 5
```

### **Edge Cases**
Test boundary conditions:
```yeep
// Empty strings
let empty = "";
print(strlen(empty));  // Should be 0

// Large numbers
let big = 999999999;
print(big * big);

// Deep recursion
fun deepRecursion(n) {
    if (n <= 0) return 0;
    return 1 + deepRecursion(n - 1);
}
print(deepRecursion(100));
```

---

## 🏗️ Development Areas

### **High Priority**
- 🐛 Bug fixes and stability improvements
- 📚 Documentation improvements
- 🧪 Test coverage expansion
- 🚀 Performance optimizations

### **Medium Priority**
- 🔧 New built-in functions
- 📝 Better error messages
- 🎯 Language feature enhancements
- 🛠️ Tooling improvements

### **Future Features**
- 📦 Arrays and collections
- 📁 File I/O operations
- 🧩 Module system
- ⚠️ Exception handling
- 📊 Standard library

### **Beginner-Friendly Tasks**
- Fix typos in documentation
- Add more example programs
- Improve error messages
- Add simple built-in functions
- Write tests for existing features

---

## 📞 Communication

### **Before Starting**
- Comment on the issue you want to work on
- Ask questions if requirements are unclear
- Discuss your approach for complex changes
- Check if someone else is already working on it

### **During Development**
- Share progress updates on the issue
- Ask for help if you get stuck
- Coordinate with other contributors
- Test thoroughly before submitting

### **GitHub Discussions**
Use [GitHub Discussions](https://github.com/Syipmong/yeep-prolag/discussions) for:
- General questions about Yeep
- Design discussions for new features
- Sharing projects built with Yeep
- Getting help with contributions

### **Issue Templates**
When creating issues, use appropriate templates:

**Bug Report:**
```markdown
## Bug Description
Brief description of the bug

## Steps to Reproduce
1. Step one
2. Step two
3. Step three

## Expected Behavior
What should happen

## Actual Behavior
What actually happens

## Environment
- OS: [Windows/Linux/macOS]
- Yeep Version: [x.x.x]
- Installation Method: [Release/Source]
```

**Feature Request:**
```markdown
## Feature Description
Clear description of the proposed feature

## Use Case
Why is this feature needed?

## Example Usage
```yeep
// Show how the feature would be used
```

## Implementation Notes
Any thoughts on implementation
```

---

## 🎯 Recognition

### **Contributors**
All contributors are recognized in:
- GitHub contributors list
- Release notes for significant contributions
- Documentation acknowledgments

### **Types of Recognition**
- 🏆 **Core Contributor**: Major features or sustained contributions
- 🐛 **Bug Hunter**: Finding and fixing important bugs
- 📚 **Documentation Hero**: Significant documentation improvements
- 🌟 **Community Helper**: Outstanding community support

---

## 📚 Resources

### **Learning Resources**
- [Language Tutorial](Language-Tutorial) - Learn Yeep basics
- [Language Reference](Language-Reference) - Complete syntax guide
- [Examples Gallery](Examples-Gallery) - Practical examples

### **Development Resources**
- [Architecture Overview](Architecture-Overview) - Internal design
- [Building from Source](Building-from-Source) - Detailed build instructions
- C Programming references and tutorials

### **External Tools**
- **Git**: Version control ([Git Tutorial](https://git-scm.com/docs/gittutorial))
- **GCC**: C compiler ([GCC Manual](https://gcc.gnu.org/onlinedocs/))
- **Make**: Build automation ([Make Manual](https://www.gnu.org/software/make/manual/))
- **Valgrind**: Memory debugging (Linux/macOS)

---

## 🤝 Code of Conduct

### **Our Values**
- **Respectful**: Treat everyone with respect and kindness
- **Inclusive**: Welcome contributors from all backgrounds
- **Collaborative**: Work together towards common goals
- **Constructive**: Provide helpful, actionable feedback

### **Expected Behavior**
- Use welcoming and inclusive language
- Respect differing viewpoints and experiences
- Accept constructive criticism gracefully
- Focus on what's best for the community
- Show empathy towards other community members

### **Unacceptable Behavior**
- Harassment, discrimination, or offensive comments
- Personal attacks or trolling
- Spam or off-topic discussions
- Sharing private information without permission

### **Reporting Issues**
If you experience or witness unacceptable behavior:
1. Contact the maintainers directly
2. Report via GitHub's reporting features
3. All reports will be handled confidentially

---

## 🎉 Thank You!

Thank you for your interest in contributing to Yeep! Every contribution, no matter how small, helps make Yeep better for everyone.

**Questions?** Don't hesitate to ask:
- 💬 [GitHub Discussions](https://github.com/Syipmong/yeep-prolag/discussions)
- 📧 Contact the maintainers
- 📖 Check other wiki pages

**Happy contributing!** 🚀
