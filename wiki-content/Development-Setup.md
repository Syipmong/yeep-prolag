# Development Setup

This guide will help you set up a development environment for contributing to the Yeep programming language project.

## Prerequisites

### Required Tools
- **Git**: For version control and repository management
- **C Compiler**: GCC (Linux/macOS) or MinGW/MSYS2 (Windows)
- **Make**: Build automation tool
- **Text Editor**: Any editor supporting C syntax highlighting

### Windows Specific
- **MSYS2**: Recommended for Windows development
- **MinGW-w64**: C compiler toolchain for Windows
- **PowerShell**: For running build scripts

### Linux/macOS Specific
- **GCC**: Usually pre-installed or available via package manager
- **Build essentials**: Development tools package

## Repository Setup

### Cloning the Repository
```bash
git clone https://github.com/YourUsername/yeep-prolag.git
cd yeep-prolag
```

### Development Branches
- `main`: Stable release branch
- `develop`: Active development branch
- `feature/*`: Feature development branches

## Build Environment

### Windows Setup
1. Install MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and install required packages:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-make
   pacman -S git
   ```
3. Add MinGW64 bin directory to PATH
4. Test the build:
   ```cmd
   build.bat
   ```

### Linux Setup
1. Install build essentials:
   ```bash
   # Ubuntu/Debian
   sudo apt update
   sudo apt install build-essential git
   
   # Fedora/RHEL
   sudo dnf groupinstall "Development Tools"
   sudo dnf install git
   
   # Arch Linux
   sudo pacman -S base-devel git
   ```
2. Test the build:
   ```bash
   make
   ```

### macOS Setup
1. Install Xcode Command Line Tools:
   ```bash
   xcode-select --install
   ```
2. Optionally install Homebrew for additional tools:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   ```
3. Test the build:
   ```bash
   make
   ```

## Project Structure

### Source Code Organization
```
yeep-prolag/
├── src/           # Main source code
│   ├── lexer.c    # Lexical analysis
│   ├── parser.c   # Syntax parsing
│   └── main.c     # Main entry point
├── include/       # Header files
├── examples/      # Example Yeep programs
├── tests/         # Test files
└── build/         # Build artifacts
```

### Key Files
- `Makefile`: Build configuration for Unix-like systems
- `build.bat`: Windows build script
- `VERSION`: Current version number
- `LANGUAGE_SPEC.md`: Language specification
- `CONTRIBUTING.md`: Contribution guidelines

## Development Workflow

### Making Changes
1. Create a feature branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
2. Make your changes in appropriate files
3. Test your changes:
   ```bash
   # Windows
   build.bat
   
   # Linux/macOS
   make clean && make
   ```
4. Run tests to ensure nothing is broken
5. Commit your changes:
   ```bash
   git add .
   git commit -m "Brief description of changes"
   ```

### Testing Changes
- Build the project successfully
- Test with existing example files
- Create new test cases for new features
- Verify no regressions in existing functionality

### Code Style Guidelines
- Use consistent indentation (4 spaces)
- Follow C naming conventions
- Add comments for complex logic
- Keep functions focused and reasonably sized
- Use meaningful variable and function names

## Debugging

### Debug Builds
- Add debug flags to your build process
- Use GDB (Linux/macOS) or similar debugger
- Add printf statements for tracing execution
- Use valgrind (Linux) for memory debugging

### Common Issues
- **Build failures**: Check compiler installation and PATH
- **Runtime errors**: Use debugger to trace execution
- **Memory issues**: Use debugging tools like valgrind
- **Platform differences**: Test on multiple platforms when possible

## IDE Configuration

### VS Code Setup
1. Install C/C++ extension
2. Configure build tasks in `.vscode/tasks.json`
3. Set up debugging configuration in `.vscode/launch.json`
4. Use the workspace settings for consistent formatting

### Other Editors
- **Vim/Neovim**: Configure for C syntax highlighting
- **Emacs**: Use C mode with appropriate settings
- **CLion**: Import as C project with Makefile

## Continuous Integration

### GitHub Actions
- Builds are automatically triggered on push
- Tests run on multiple platforms
- Release artifacts are generated automatically

### Local Testing
- Test builds on your target platform
- Run all example files to verify functionality
- Check for memory leaks and segmentation faults

## Release Process

### Version Management
1. Update `VERSION` file
2. Update documentation as needed
3. Create release notes
4. Tag the release:
   ```bash
   git tag -a v1.0.x -m "Release version 1.0.x"
   git push origin v1.0.x
   ```

### Release Checklist
- [ ] All tests pass
- [ ] Documentation is updated
- [ ] Version number is incremented
- [ ] Release notes are prepared
- [ ] Build artifacts are verified

## Getting Help

### Resources
- **GitHub Issues**: Report bugs and request features
- **Discussions**: Ask questions and share ideas
- **Wiki**: Comprehensive documentation
- **Code Comments**: In-line documentation

### Community
- Follow coding standards and contribution guidelines
- Be respectful and helpful to other contributors
- Test your changes thoroughly before submitting
- Write clear commit messages and pull request descriptions

---

This development setup guide should help you get started contributing to the Yeep programming language. If you encounter any issues, please feel free to open a GitHub issue or start a discussion.
