#!/bin/bash

# Yeep Release Build Script
# Creates distribution packages for all platforms

set -e

VERSION=$(cat VERSION)
echo "Building Yeep v$VERSION for distribution..."

# Clean previous builds
echo "Cleaning previous builds..."
make clean
rm -rf dist/

# Create distribution directory
mkdir -p dist

echo "Building Yeep..."
make

# Test the build
echo "Testing build..."
echo 'print("Build test successful!");' | ./build/yeep

# Create Linux package
echo "Creating Linux package..."
mkdir -p dist/yeep-linux-x64
cp build/yeep dist/yeep-linux-x64/
cp install.sh dist/yeep-linux-x64/
cp README.md dist/yeep-linux-x64/
cp LICENSE dist/yeep-linux-x64/
cp -r examples dist/yeep-linux-x64/
cd dist
tar -czf yeep-linux-x64.tar.gz yeep-linux-x64/
cd ..

echo "Distribution package created: dist/yeep-linux-x64.tar.gz"
echo ""
echo "To create packages for other platforms:"
echo "  Windows: Use GitHub Actions or cross-compile with MinGW"
echo "  macOS: Use GitHub Actions or build on macOS"
echo ""
echo "Upload these files to GitHub Releases for distribution."
