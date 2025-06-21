#!/bin/bash
# Official Yeep C++ Build Script - Unix Version
# Builds the working Yeep interpreter for Linux/macOS

echo "========================================"
echo "Building Yeep Programming Language"
echo "C++ Version 2.0.0 - OFFICIAL RELEASE"
echo "Platform: $(uname -s)"
echo "========================================"

# Check for required tools
if ! command -v g++ &> /dev/null; then
    echo "❌ ERROR: g++ compiler not found!"
    echo "Please install g++ with C++17 support:"
    echo ""
    echo "Ubuntu/Debian: sudo apt install g++"
    echo "Fedora: sudo dnf install gcc-c++"
    echo "macOS: brew install gcc"
    echo ""
    exit 1
fi

echo "✅ Found g++ compiler: $(g++ --version | head -n1)"

# Create build directories
echo ""
echo "Creating build directories..."
mkdir -p build/core

# Build process
echo ""
echo "[1/5] Compiling main.cpp..."
g++ -Wall -Wextra -std=c++17 -I include -c src/main.cpp -o build/main.o
if [ $? -ne 0 ]; then
    echo "❌ Failed to compile main.cpp"
    exit 1
fi

echo "[2/5] Compiling YeepEngine.cpp..."
g++ -Wall -Wextra -std=c++17 -I include -c src/core/YeepEngine.cpp -o build/core/YeepEngine.o
if [ $? -ne 0 ]; then
    echo "❌ Failed to compile YeepEngine.cpp"
    exit 1
fi

echo "[3/5] Compiling Token.cpp..."
g++ -Wall -Wextra -std=c++17 -I include -c src/core/Token.cpp -o build/core/Token.o
if [ $? -ne 0 ]; then
    echo "❌ Failed to compile Token.cpp"
    exit 1
fi

echo "[4/5] Compiling Lexer.cpp..."
g++ -Wall -Wextra -std=c++17 -I include -c src/core/Lexer.cpp -o build/core/Lexer.o
if [ $? -ne 0 ]; then
    echo "❌ Failed to compile Lexer.cpp"
    exit 1
fi

echo "[5/5] Linking executable..."
g++ build/main.o build/core/YeepEngine.o build/core/Token.o build/core/Lexer.o -o build/yeep
if [ $? -ne 0 ]; then
    echo "❌ Failed to link executable"
    exit 1
fi

# Make executable
chmod +x build/yeep

echo ""
echo "========================================"
echo "BUILD SUCCESSFUL! ✅"
echo "========================================"
echo ""
echo "Executable: build/yeep"
echo ""
echo "Test with:"
echo "  ./build/yeep              (Interactive mode)"
echo "  ./build/yeep demo_v2.yeep (Run demo script)"
echo ""
echo "Install with:"
echo "  sudo cp build/yeep /usr/local/bin/yeep"
echo ""
