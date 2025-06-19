#!/bin/bash

# Quick installer script that can be downloaded and run directly
# Usage: curl -fsSL https://raw.githubusercontent.com/syipmong/yeep-prolag/main/install-quick.sh | bash

set -e

echo "🚀 Installing Yeep Programming Language..."

# Detect platform
PLATFORM=""
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    PLATFORM="linux-x64"
elif [[ "$OSTYPE" == "darwin"* ]]; then
    PLATFORM="macos-x64"
else
    echo "❌ Unsupported platform: $OSTYPE"
    echo "Please download manually from: https://github.com/syipmong/yeep-prolag/releases"
    exit 1
fi

# Get latest release URL
LATEST_URL="https://api.github.com/repos/syipmong/yeep-prolag/releases/latest"
DOWNLOAD_URL=$(curl -s "$LATEST_URL" | grep "browser_download_url.*$PLATFORM.tar.gz" | cut -d '"' -f 4)

if [ -z "$DOWNLOAD_URL" ]; then
    echo "❌ Could not find download URL for $PLATFORM"
    echo "Please download manually from: https://github.com/syipmong/yeep-prolag/releases"
    exit 1
fi

echo "📥 Downloading Yeep for $PLATFORM..."

# Create temp directory
TEMP_DIR=$(mktemp -d)
cd "$TEMP_DIR"

# Download and extract
curl -L -o yeep.tar.gz "$DOWNLOAD_URL"
tar -xzf yeep.tar.gz

# Find the extracted directory
EXTRACTED_DIR=$(find . -name "yeep-*" -type d | head -n 1)
cd "$EXTRACTED_DIR"

# Make install script executable and run it
chmod +x install.sh
echo "🔧 Installing Yeep..."

if [ "$EUID" -eq 0 ]; then
    ./install.sh
else
    echo "📋 Choose installation type:"
    echo "1) Install for current user (recommended)"
    echo "2) Install system-wide (requires sudo)"
    read -p "Enter choice (1 or 2): " choice
    
    case $choice in
        1)
            ./install.sh
            ;;
        2)
            sudo ./install.sh
            ;;
        *)
            echo "Invalid choice. Installing for current user..."
            ./install.sh
            ;;
    esac
fi

# Cleanup
cd /
rm -rf "$TEMP_DIR"

echo "✅ Yeep installation complete!"
echo ""
echo "🎉 Try it out:"
echo "  yeep --version"
echo "  yeep --help"
echo ""
echo "📖 Learn more: https://github.com/syipmong/yeep-prolag"
