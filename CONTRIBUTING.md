# Contributing to Yeep Programming Language

Thank you for your interest in contributing to Yeep! We welcome contributions of all kinds.

## 🚀 Quick Start

1. **Fork** the repository
2. **Clone** your fork:
   ```bash
   git clone https://github.com/syipmong/yeep-prolag.git
   cd yeep-prolag
   ```
3. **Build** and test:
   ```bash
   make clean && make
   echo 'print("Hello, Yeep!");' | ./build/yeep
   ```

## 📋 How to Contribute

### 🐛 Reporting Bugs
- Use the [Bug Report template](.github/ISSUE_TEMPLATE/bug_report.md)
- Include steps to reproduce, expected vs actual behavior
- Provide your OS, Yeep version, and error messages

### 💡 Requesting Features
- Use the [Feature Request template](.github/ISSUE_TEMPLATE/feature_request.md)
- Describe the use case and proposed solution
- Include code examples if applicable

### 🔧 Code Contributions

#### Getting Started
1. Check [open issues](https://github.com/syipmong/yeep-prolag/issues) for tasks
2. Comment on an issue to claim it
3. Create a new branch for your work:
   ```bash
   git checkout -b feature/your-feature-name
   ```

#### Development Setup
```bash
# Build the project
make clean && make

# Run tests
make test  # (when available)

# Test manually
echo 'print("test");' | ./build/yeep
```

#### Code Style
- **C Code**: Follow existing style in the codebase
- **Comments**: Use clear, descriptive comments
- **Functions**: Keep functions focused and well-named
- **Error Handling**: Always check for error conditions

#### Making Changes
1. **Write code** following the project style
2. **Test thoroughly**:
   ```bash
   # Test basic functionality
   ./build/yeep examples/hello.yeep
   
   # Test new features
   echo 'your_test_code_here;' | ./build/yeep
   ```
3. **Update documentation** if needed
4. **Commit** with clear messages:
   ```bash
   git commit -m "Add: logical OR operator with short-circuit evaluation"
   ```

#### Submitting Changes
1. **Push** your branch:
   ```bash
   git push origin feature/your-feature-name
   ```
2. **Create a Pull Request** with:
   - Clear title and description
   - Reference any related issues
   - Include test cases or examples

## 🏗️ Project Structure

```
yeep-prolag/
├── src/                 # Source code
│   ├── main.c          # Entry point and CLI
│   ├── lexer.c         # Tokenization
│   ├── parser.c        # AST generation
│   ├── interpreter.c   # Execution engine
│   └── shell.c         # REPL and file execution
├── include/            # Header files
│   └── yeep.h          # Main header
├── examples/           # Example programs
├── .github/            # GitHub templates and workflows
└── build/              # Compiled binaries
```

## 🧪 Testing

### Manual Testing
```bash
# Test REPL
./build/yeep

# Test file execution
./build/yeep examples/hello.yeep

# Test specific features
echo 'print("test: " + (true && false));' | ./build/yeep
```

### Feature Testing Checklist
- [ ] Compiles without warnings
- [ ] REPL works correctly
- [ ] File execution works
- [ ] New syntax is parsed correctly
- [ ] Error messages are clear
- [ ] Cross-platform compatibility

## 📝 Documentation

### Update Documentation For:
- New language features → Update `README.md` syntax section
- New CLI options → Update usage section
- Breaking changes → Update changelog
- Installation changes → Update installation instructions

## 🔄 Release Process

1. **Update version** in `VERSION` file
2. **Update `README.md`** with new features
3. **Create a tag**:
   ```bash
   git tag -a v1.1.0 -m "Release v1.1.0"
   git push origin v1.1.0
   ```
4. **GitHub Actions** will automatically build and create a release

## 🤝 Community Guidelines

- **Be respectful** and constructive in discussions
- **Help others** learn and contribute
- **Follow** the project's coding standards
- **Test** your changes thoroughly
- **Document** new features and breaking changes

## 📞 Getting Help

- **Issues**: Create an issue for bugs or questions
- **Discussions**: Use GitHub Discussions for general questions
- **Documentation**: Check the README and code comments

Thank you for contributing to Yeep! 🎉
