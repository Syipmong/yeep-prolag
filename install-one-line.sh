#!/bin/bash
# Yeep Programming Language v2.0.0 - One-Line Installer for Unix Systems
# Usage: curl -fsSL https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.sh | bash

set -e

echo "🎉 Installing Yeep Programming Language v2.0.0..."
echo "================================================="

# Detect platform
PLATFORM=$(uname -s | tr '[:upper:]' '[:lower:]')
ARCH=$(uname -m)

# Map architecture
case $ARCH in
    x86_64) ARCH="x64" ;;
    amd64) ARCH="x64" ;;
    arm64) ARCH="arm64" ;;
    aarch64) ARCH="arm64" ;;
    *) echo "❌ Unsupported architecture: $ARCH"; exit 1 ;;
esac

# Determine download URL
RELEASE_URL="https://github.com/Syipmong/yeep-prolag/releases/latest/download"
case $PLATFORM in
    linux)
        ARCHIVE="yeep-v2.0.0-linux.tar.gz"
        ;;
    darwin)
        ARCHIVE="yeep-v2.0.0-macos.tar.gz"
        ;;
    *)
        echo "❌ Unsupported platform: $PLATFORM"
        echo "💡 For Windows, use: iwr -useb https://raw.githubusercontent.com/Syipmong/yeep-prolag/main/install-one-line.ps1 | iex"
        exit 1
        ;;
esac

DOWNLOAD_URL="$RELEASE_URL/$ARCHIVE"

# Create temporary directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

echo "📥 Downloading Yeep v2.0.0 for $PLATFORM..."

# Download with fallback
if command -v curl >/dev/null 2>&1; then
    curl -L "$DOWNLOAD_URL" -o "$ARCHIVE"
elif command -v wget >/dev/null 2>&1; then
    wget "$DOWNLOAD_URL" -O "$ARCHIVE"
else
    echo "❌ Neither curl nor wget found. Please install one of them."
    exit 1
fi

echo "📦 Extracting archive..."
tar -xzf "$ARCHIVE"

# Find extracted directory
EXTRACT_DIR=$(find . -maxdepth 1 -type d -name "yeep-v2.0.0-*" | head -1)
if [ -z "$EXTRACT_DIR" ]; then
    echo "❌ Failed to find extracted directory"
    exit 1
fi

cd "$EXTRACT_DIR"

echo "🔧 Installing Yeep..."

# Install based on permissions
if [ -w "/usr/local/bin" ] || [ "$EUID" -eq 0 ]; then
    # System install
    cp yeep /usr/local/bin/yeep
    chmod +x /usr/local/bin/yeep
    echo "✅ Yeep installed to /usr/local/bin/yeep"
else
    # User install
    mkdir -p "$HOME/.local/bin"
    cp yeep "$HOME/.local/bin/yeep"
    chmod +x "$HOME/.local/bin/yeep"
    
    # Add to PATH if not already there
    if [[ ":$PATH:" != *":$HOME/.local/bin:"* ]]; then
        echo 'export PATH="$HOME/.local/bin:$PATH"' >> "$HOME/.bashrc"
        echo "📝 Added $HOME/.local/bin to PATH in ~/.bashrc"
        echo "💡 Run 'source ~/.bashrc' or restart your terminal"
    fi
    
    echo "✅ Yeep installed to $HOME/.local/bin/yeep"
fi

# Cleanup
cd /
rm -rf "$TEMP_DIR"

echo ""
echo "🎊 Installation complete!"
echo ""
echo "📖 Quick start:"
echo "   yeep                 # Start interactive REPL"
echo "   yeep script.yeep     # Run a script file"
echo ""
echo "🔗 Documentation: https://github.com/Syipmong/yeep-prolag"
echo "💬 Issues: https://github.com/Syipmong/yeep-prolag/issues"
echo ""

# Test installation
if command -v yeep >/dev/null 2>&1; then
    echo "✅ Installation verified - 'yeep' command is available!"
    echo ""
    echo "🧪 Testing with a simple script..."
    echo 'print("Hello from Yeep v2.0.0!");' | yeep
else
    echo "⚠️  'yeep' command not found in PATH"
    echo "💡 You may need to restart your terminal or run 'source ~/.bashrc'"
fi
