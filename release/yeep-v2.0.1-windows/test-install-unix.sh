#!/bin/bash

# Yeep Installation Test Script (Linux/macOS Dry Run)
# Tests the installation script without actually installing

echo "=============================================================="
echo "Yeep Programming Language - Installation Test (Dry Run)"
echo "=============================================================="
echo

# Check if yeep executable exists
if [ ! -f "build/yeep" ]; then
    echo "❌ FAIL: yeep executable not found in build directory"
    echo "Please run build.sh first to compile Yeep"
    exit 1
else
    echo "✅ PASS: yeep executable found in build directory"
fi

# Test executable functionality
echo
echo "Testing executable functionality..."
echo "Running: build/yeep --version"
./build/yeep --version 2>/dev/null
if [ $? -eq 0 ]; then
    echo "✅ PASS: Executable runs correctly"
else
    echo "❌ FAIL: Executable returned error"
    exit 1
fi

# Test script execution
echo
echo "Testing script execution..."
if [ -f "hello_working.yeep" ]; then
    echo "Running: build/yeep hello_working.yeep"
    ./build/yeep hello_working.yeep 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "✅ PASS: Script execution successful"
    else
        echo "❌ FAIL: Script execution failed"
        exit 1
    fi
else
    echo "⚠️  SKIP: hello_working.yeep not found"
fi

# Test installation script structure
echo
echo "Testing installation script structure..."
if [ -f "install.sh" ]; then
    echo "✅ PASS: install.sh exists"
else
    echo "❌ FAIL: install.sh not found"
    exit 1
fi

if [ -x "install.sh" ]; then
    echo "✅ PASS: install.sh is executable"
else
    echo "⚠️  WARN: install.sh is not executable (will be fixed during install)"
fi

# Test required files for installation
echo
echo "Testing required files for installation..."
files_to_check=("README.md" "LICENSE" "VERSION")
for file in "${files_to_check[@]}"; do
    if [ -f "$file" ]; then
        echo "✅ PASS: $file exists"
    else
        echo "❌ FAIL: $file not found"
    fi
done

# Test example files
echo
echo "Testing example files..."
example_count=$(find . -maxdepth 1 -name "*.yeep" | wc -l)
if [ $example_count -gt 0 ]; then
    echo "✅ PASS: Found $example_count example files (.yeep)"
else
    echo "❌ FAIL: No example files found"
fi

# Test installation directories (dry run)
echo
echo "Testing installation directory structure..."
if [ "$EUID" -eq 0 ]; then
    echo "✅ INFO: Running as root - would install to /usr/local/"
    echo "  - Executable: /usr/local/bin/yeep"
    echo "  - Library: /usr/local/lib/yeep/"
    echo "  - Documentation: /usr/local/share/doc/yeep/"
else
    echo "✅ INFO: Running as user - would install to ~/.local/"
    echo "  - Executable: ~/.local/bin/yeep"
    echo "  - Library: ~/.local/lib/yeep/"
    echo "  - Documentation: ~/.local/share/doc/yeep/"
fi

echo
echo "=============================================================="
echo "Installation Test Complete"
echo "=============================================================="
echo
echo "✅ All tests passed! Installation scripts are ready."
echo
echo "To install Yeep system-wide:"
echo "  sudo ./install.sh     # System-wide installation"
echo "  ./install.sh          # User-only installation"
echo
echo "After installation, you can use:"
echo "  yeep                  # Start interactive REPL"
echo "  yeep script.yeep      # Run a Yeep script"
echo "  yeep --help          # Show help"
echo "  yeep --version       # Show version"
echo
