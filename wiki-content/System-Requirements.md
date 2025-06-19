# System Requirements

This page outlines the system requirements and compatibility information for the Yeep programming language.

## Minimum System Requirements

### Hardware Requirements

#### Processor
- **x86-64 (64-bit)**: Intel or AMD processor
- **Minimum Speed**: 1 GHz or faster
- **Recommended**: 2 GHz dual-core or better

#### Memory (RAM)
- **Minimum**: 512 MB RAM
- **Recommended**: 2 GB RAM or more
- **For Development**: 4 GB RAM or more

#### Storage
- **Installation**: 10 MB for Yeep interpreter
- **Development**: 100 MB for full development environment
- **Projects**: Variable, depending on project size

#### Display
- **Text-based**: Any display capable of showing text
- **Resolution**: 800x600 minimum for development tools
- **Color**: Not required, but helpful for syntax highlighting

### Software Requirements

#### Operating Systems

##### Windows
- **Supported Versions**:
  - Windows 10 (64-bit) - Recommended
  - Windows 11 (64-bit) - Recommended
  - Windows 8.1 (64-bit) - Limited support
  - Windows Server 2016 or later

- **Required Components**:
  - PowerShell 5.0 or later (usually included)
  - .NET Framework 4.5 or later (usually included)
  - Windows Terminal (recommended for better experience)

##### Linux
- **Supported Distributions**:
  - Ubuntu 18.04 LTS or later
  - Debian 9 (Stretch) or later
  - CentOS 7 or later
  - Fedora 30 or later
  - Arch Linux (latest)
  - openSUSE Leap 15.0 or later

- **Required Components**:
  - glibc 2.17 or later
  - bash shell
  - Standard POSIX utilities

##### macOS
- **Supported Versions**:
  - macOS 10.14 (Mojave) or later
  - macOS 11.0 (Big Sur) - Recommended
  - macOS 12.0 (Monterey) - Recommended
  - macOS 13.0 (Ventura) or later

- **Required Components**:
  - Command Line Tools for Xcode
  - Terminal application

## Development Requirements

### For Building from Source

#### Compiler Requirements
- **C Compiler**: C99-compliant compiler required
- **Windows**: MinGW-w64 or MSYS2 with GCC
- **Linux**: GCC 4.8 or later, Clang 3.9 or later
- **macOS**: Xcode Command Line Tools (includes Clang)

#### Build Tools
- **Make**: GNU Make 3.81 or later
- **Git**: For version control (2.0 or later recommended)
- **Text Editor**: Any editor for source code editing

#### Optional Development Tools
- **Debugger**: GDB (Linux/macOS), MinGW-w64 GDB (Windows)
- **IDE**: VS Code, CLion, or similar C-capable IDE
- **Memory Tools**: Valgrind (Linux), AddressSanitizer

### For Contributing

#### Version Control
- **Git**: Latest stable version
- **GitHub Account**: For contributing to the project
- **SSH Keys**: Configured for GitHub access

#### Testing Environment
- **Multiple Platforms**: Access to test on different OS
- **Virtual Machines**: For cross-platform testing
- **Container Tools**: Docker (optional, for isolated testing)

## Runtime Dependencies

### Yeep Interpreter
- **No External Dependencies**: Statically linked executable
- **Standard Libraries**: Only system-provided C runtime
- **Network**: Not required for basic operation

### Installation Dependencies
- **Internet Connection**: Required for downloading releases
- **Archive Tool**: For extracting ZIP files (usually built-in)
- **Administrative Rights**: May be needed for system-wide installation

## Performance Characteristics

### Memory Usage
- **Base Memory**: ~1-5 MB for interpreter
- **Per Program**: Variable based on program complexity
- **Garbage Collection**: Minimal overhead for simple programs

### CPU Usage
- **Idle**: Near-zero CPU usage when not executing
- **Execution**: Proportional to program complexity
- **Multi-core**: Single-threaded execution (multi-threading planned)

### File System
- **Permissions**: Read access to source files
- **Temporary Files**: May create temporary files during execution
- **Configuration**: Stores minimal configuration data

## Compatibility Matrix

### Architecture Support
| Architecture | Windows | Linux | macOS | Status |
|--------------|---------|-------|-------|--------|
| x86-64       | ✅      | ✅    | ✅    | Full Support |
| x86 (32-bit) | ⚠️      | ⚠️    | ❌    | Limited Support |
| ARM64        | 🔄      | 🔄    | 🔄    | In Development |
| ARM (32-bit) | ❌      | ⚠️    | ❌    | Limited Support |

**Legend:**
- ✅ Full Support
- ⚠️ Limited/Community Support
- 🔄 In Development
- ❌ Not Supported

### Compiler Compatibility
| Compiler | Version | Windows | Linux | macOS | Notes |
|----------|---------|---------|-------|-------|-------|
| GCC      | 4.8+    | ✅      | ✅    | ✅    | Recommended |
| Clang    | 3.9+    | ✅      | ✅    | ✅    | macOS default |
| MSVC     | 2017+   | 🔄      | ❌    | ❌    | Under consideration |
| Intel CC | 19+     | ⚠️      | ⚠️    | ⚠️    | Community tested |

## Network Requirements

### Installation
- **Bandwidth**: Minimal (< 1 MB download)
- **Protocols**: HTTPS for secure downloads
- **Firewall**: Standard web access (port 443)

### Development
- **Git Protocol**: For repository access
- **Package Managers**: For development dependencies
- **Documentation**: Online access for latest docs

## Security Requirements

### Execution Permissions
- **File System**: Read access to source files
- **Memory**: Standard user memory allocation
- **Network**: No network access required for basic operation

### Installation Permissions
- **User Installation**: No special permissions required
- **System Installation**: Administrator/root access may be needed
- **PATH Modification**: May require elevated permissions

## Troubleshooting Requirements

### Common Issues
- **Missing Dependencies**: Ensure C runtime is available
- **Permission Errors**: Check file and directory permissions
- **PATH Issues**: Verify installation directory is in PATH

### Diagnostic Tools
- **System Information**: OS version, architecture details
- **Error Messages**: Full error output for troubleshooting
- **Log Files**: Debug output and installation logs

## Future Compatibility

### Planned Support
- **ARM Architecture**: Native ARM64 support
- **More Platforms**: FreeBSD, other Unix variants
- **Container Support**: Docker images and containerization
- **Mobile Platforms**: Potential iOS/Android support

### Deprecation Policy
- **Legacy Systems**: 2-year support after version end-of-life
- **Migration Path**: Clear upgrade instructions provided
- **Compatibility Warnings**: Advance notice of breaking changes

---

## Getting Help

If your system doesn't meet these requirements or you encounter compatibility issues:

1. **Check the [Troubleshooting Guide](Troubleshooting)** for common solutions
2. **Review the [Installation Guide](Installation-Guide)** for platform-specific instructions
3. **Search [GitHub Issues](https://github.com/itsthatblackhat/yeep-prolag/issues)** for similar problems
4. **Create a new issue** with your system specifications if needed

For the most current compatibility information, check the [GitHub repository](https://github.com/itsthatblackhat/yeep-prolag) and project announcements.
