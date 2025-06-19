#!/bin/bash
# Yeep Programming Language v2.0.0 - One-Click Installer
# Downloads, builds, and installs Yeep for Linux/macOS

set -e

echo "🎉 Yeep Programming Language v2.0.0 Installer"
echo "=============================================="
echo ""

# Detect OS
OS=$(uname -s)
case "$OS" in
    Linux*)     PLATFORM="linux";;
    Darwin*)    PLATFORM="macos";;
    *)          echo "❌ Unsupported OS: $OS"; exit 1;;
esac

echo "🖥️  Platform detected: $PLATFORM"
echo ""

# Check dependencies
echo "🔍 Checking dependencies..."

if ! command -v curl &> /dev/null && ! command -v wget &> /dev/null; then
    echo "❌ Neither curl nor wget found. Please install one of them."
    exit 1
fi

if ! command -v g++ &> /dev/null; then
    echo "❌ g++ compiler not found!"
    echo ""
    echo "Please install g++ first:"
    case "$PLATFORM" in
        linux)
            echo "  Ubuntu/Debian: sudo apt install g++"
            echo "  Fedora: sudo dnf install gcc-c++"
            echo "  Arch: sudo pacman -S gcc"
            ;;
        macos)
            echo "  macOS: brew install gcc"
            echo "  Or: xcode-select --install"
            ;;
    esac
    echo ""
    exit 1
fi

echo "✅ Dependencies OK"
echo ""

# Create temporary directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

echo "📥 Downloading Yeep v2.0.0 source..."

# Clone repository
if command -v git &> /dev/null; then
    git clone https://github.com/Syipmong/yeep-prolag.git
    cd yeep-prolag
else
    echo "❌ Git not found. Please install git."
    exit 1
fi

echo ""
echo "🔨 Building Yeep..."

# Build
chmod +x build_official.sh
./build_official.sh

echo ""
echo "📦 Installing Yeep..."

# Install system-wide
echo "Installing system-wide to /usr/local/bin..."
sudo cp build/yeep /usr/local/bin/yeep
sudo chmod +x /usr/local/bin/yeep

# Cleanup
cd /
rm -rf "$TEMP_DIR"

echo ""
echo "🎉 Installation complete!"
echo "================================"
echo ""
echo "✅ Yeep v2.0.0 installed successfully!"
echo ""
echo "🚀 Quick start:"
echo "  yeep                    # Interactive mode"
echo "  yeep script.yeep        # Run a script"
echo ""

# Test installation
echo "🧪 Testing installation..."
echo 'print("Installation test successful! 🎉");' | yeep

echo ""
echo "Welcome to Yeep Programming Language! 🎊"
