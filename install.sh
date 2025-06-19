#!/bin/bash

# Yeep Programming Language Installation Script
# For Unix/Linux/macOS systems

set -e

echo "Installing Yeep Programming Language..."

# Check if running as root for system-wide installation
if [ "$EUID" -eq 0 ]; then
    INSTALL_DIR="/usr/local/bin"
    LIB_DIR="/usr/local/lib/yeep"
    echo "Installing system-wide to $INSTALL_DIR"
else
    INSTALL_DIR="$HOME/.local/bin"
    LIB_DIR="$HOME/.local/lib/yeep"
    echo "Installing for current user to $INSTALL_DIR"
    echo "Note: Run with sudo for system-wide installation"
fi

# Create directories
mkdir -p "$INSTALL_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$LIB_DIR/examples"

# Build if needed
if [ ! -f "build/yeep" ]; then
    echo "Building Yeep..."
    if [ -f "Makefile" ]; then
        make clean && make
    else
        # Fallback build command
        gcc -o build/yeep src/*.c -I include
    fi
fi

# Copy files
echo "Installing files..."
cp build/yeep "$INSTALL_DIR/"
cp README.md "$LIB_DIR/"
cp LANGUAGE_SPEC.md "$LIB_DIR/"
cp examples/* "$LIB_DIR/examples/"

# Make executable
chmod +x "$INSTALL_DIR/yeep"

# Check if already in PATH
if echo "$PATH" | grep -q "$INSTALL_DIR"; then
    echo "Directory $INSTALL_DIR is already in PATH"
else
    echo "Adding $INSTALL_DIR to PATH..."
    
    # Add to shell profile
    SHELL_PROFILE=""
    if [ -f "$HOME/.bashrc" ]; then
        SHELL_PROFILE="$HOME/.bashrc"
    elif [ -f "$HOME/.zshrc" ]; then
        SHELL_PROFILE="$HOME/.zshrc"
    elif [ -f "$HOME/.profile" ]; then
        SHELL_PROFILE="$HOME/.profile"
    fi
    
    if [ -n "$SHELL_PROFILE" ]; then
        echo "export PATH=\"$INSTALL_DIR:\$PATH\"" >> "$SHELL_PROFILE"
        echo "Added to $SHELL_PROFILE"
        echo "Please run: source $SHELL_PROFILE"
    else
        echo "Please manually add $INSTALL_DIR to your PATH"
    fi
fi

echo ""
echo "Installation completed!"
echo "Yeep is installed to: $INSTALL_DIR/yeep"
echo "Examples are in: $LIB_DIR/examples"
echo ""
echo "Usage:"
echo "  yeep                    - Start interactive shell"
echo "  yeep script.yeep        - Run a Yeep script"
echo "  yeep $LIB_DIR/examples/hello.yeep - Run example"
echo ""
echo "You may need to restart your terminal or run 'source ~/.bashrc' for PATH changes to take effect."
