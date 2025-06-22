#!/bin/bash

# ================================================================
# Yeep Programming Language v2.0.4 - System-Wide Installation
# ================================================================

set -e

echo
echo "╔══════════════════════════════════════════════════════════════╗"
echo "║                🎯 Yeep Programming Language v2.0.4          ║"
echo "║                                                              ║"
echo "║                  System-Wide Installation                    ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo

# Check if yeep executable exists
if [ ! -f "build/yeep" ]; then
    echo "❌ Error: yeep executable not found in build directory"
    echo "Please run build.sh first to compile Yeep"
    echo
    exit 1
fi

# Determine installation directories
if [ "$EUID" -eq 0 ]; then
    echo "✅ Running with root privileges"
    INSTALL_TYPE="system"
    INSTALL_DIR="/usr/local/bin"
    LIB_DIR="/usr/local/lib/yeep"
    DOC_DIR="/usr/local/share/doc/yeep"
else
    echo "⚠️  Not running as root"
    echo "Installing to user directory instead"
    INSTALL_TYPE="user"
    INSTALL_DIR="$HOME/.local/bin"
    LIB_DIR="$HOME/.local/lib/yeep"
    DOC_DIR="$HOME/.local/share/doc/yeep"
fi

echo
echo "📁 Installation Directory: $INSTALL_DIR"
echo "📚 Library Directory: $LIB_DIR"
echo "📖 Documentation Directory: $DOC_DIR"
echo "🔧 Installation Type: $INSTALL_TYPE"
echo

# Create installation directories
echo "📂 Creating installation directories..."
mkdir -p "$INSTALL_DIR"
mkdir -p "$LIB_DIR"
mkdir -p "$DOC_DIR"
mkdir -p "$LIB_DIR/examples"

# Copy executable
echo "📋 Copying yeep executable..."
cp "build/yeep" "$INSTALL_DIR/yeep"
chmod +x "$INSTALL_DIR/yeep"

# Copy documentation files
echo "📋 Copying documentation..."
[ -f "README.md" ] && cp "README.md" "$DOC_DIR/"
[ -f "LICENSE" ] && cp "LICENSE" "$DOC_DIR/"
[ -f "VERSION" ] && cp "VERSION" "$DOC_DIR/"
[ -f "RELEASE-v2.0.1.md" ] && cp "RELEASE-v2.0.1.md" "$DOC_DIR/RELEASE-NOTES.md"
[ -f "LANGUAGE_SPEC.md" ] && cp "LANGUAGE_SPEC.md" "$DOC_DIR/"
[ -f "USAGE.md" ] && cp "USAGE.md" "$DOC_DIR/"

# Copy example files
echo "📋 Copying examples..."
for file in *.yeep; do
    [ -f "$file" ] && cp "$file" "$LIB_DIR/examples/"
done

# Create uninstall script
echo "📋 Creating uninstall script..."
cat > "$LIB_DIR/uninstall.sh" << 'EOF'
#!/bin/bash
echo "Uninstalling Yeep Programming Language..."

# Remove executable
rm -f "$INSTALL_DIR/yeep"

# Remove directories
rm -rf "$LIB_DIR"
rm -rf "$DOC_DIR"

# Remove from PATH (basic cleanup)
if [ -f "$HOME/.bashrc" ]; then
    sed -i '/export PATH.*yeep/d' "$HOME/.bashrc"
fi
if [ -f "$HOME/.zshrc" ]; then
    sed -i '/export PATH.*yeep/d' "$HOME/.zshrc"
fi
if [ -f "$HOME/.profile" ]; then
    sed -i '/export PATH.*yeep/d' "$HOME/.profile"
fi

echo "✅ Yeep has been uninstalled successfully"
EOF

# Make the uninstall script executable
chmod +x "$LIB_DIR/uninstall.sh"

# Add to PATH if needed
echo "🔧 Adding to system PATH..."

if echo "$PATH" | grep -q "$INSTALL_DIR"; then
    echo "ℹ️  Already in PATH"
else
    # Determine which shell profile to use
    SHELL_PROFILE=""
    if [ -n "$ZSH_VERSION" ]; then
        SHELL_PROFILE="$HOME/.zshrc"
    elif [ -n "$BASH_VERSION" ]; then
        SHELL_PROFILE="$HOME/.bashrc"
    elif [ -f "$HOME/.zshrc" ]; then
        SHELL_PROFILE="$HOME/.zshrc"
    elif [ -f "$HOME/.bashrc" ]; then
        SHELL_PROFILE="$HOME/.bashrc"
    elif [ -f "$HOME/.profile" ]; then
        SHELL_PROFILE="$HOME/.profile"
    fi
    
    if [ -n "$SHELL_PROFILE" ]; then
        echo "export PATH=\"$INSTALL_DIR:\$PATH\"" >> "$SHELL_PROFILE"
        echo "✅ Added to PATH in $SHELL_PROFILE"
    else
        echo "⚠️  Could not automatically add to PATH"
        echo "Please manually add $INSTALL_DIR to your PATH"
    fi
fi

echo
echo "╔══════════════════════════════════════════════════════════════╗"
echo "║                 ✅ INSTALLATION COMPLETE!                   ║"
echo "║                                                              ║"
echo "║  Yeep v2.0.3 has been installed successfully!               ║"
echo "║                                                              ║"
echo "║  📁 Location: $INSTALL_DIR/yeep                    ║"
echo "║  📚 Examples: $LIB_DIR/examples/                   ║"
echo "║  📖 Docs: $DOC_DIR/                                ║"
echo "║                                                              ║"
echo "║  🚀 Usage:                                                   ║"
echo "║     yeep              # Start interactive REPL              ║"
echo "║     yeep script.yeep  # Run a Yeep script                   ║"
echo "║     yeep --help       # Show help                           ║"
echo "║     yeep --version    # Show version                        ║"
echo "║                                                              ║"
echo "║  🗑️  Uninstall: $LIB_DIR/uninstall.sh          ║"
echo "╚══════════════════════════════════════════════════════════════╝"
echo
echo "⚠️  Important: Please restart your terminal or run:"
if [ -n "$SHELL_PROFILE" ]; then
    echo "    source $SHELL_PROFILE"
else
    echo "    source ~/.bashrc  # or ~/.zshrc"
fi
echo "    to use the 'yeep' command from anywhere!"
echo
echo "🎉 Ready to code in Yeep! Try: yeep --help"
echo
