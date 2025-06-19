@echo off
REM Official Yeep C++ Build Script - WORKING VERSION
echo ========================================
echo Building Yeep Programming Language
echo C++ Version 1.2.0 - WORKING ✅
echo ========================================

REM Create build directories
if not exist build mkdir build
if not exist build\core mkdir build\core

echo.
echo [1/5] Compiling main.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\main.cpp -o build\main.o
if errorlevel 1 goto error

echo [2/5] Compiling YeepEngine.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\YeepEngine.cpp -o build\core\YeepEngine.o
if errorlevel 1 goto error

echo [3/5] Compiling Token.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Token.cpp -o build\core\Token.o
if errorlevel 1 goto error

echo [4/5] Compiling Lexer.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Lexer.cpp -o build\core\Lexer.o
if errorlevel 1 goto error

echo [5/5] Linking executable...
g++ build\main.o build\core\YeepEngine.o build\core\Token.o build\core\Lexer.o -o build\yeep.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo BUILD SUCCESSFUL! ✅
echo ========================================
    echo 1. MSYS2 with GCC, or
    echo 2. MinGW-w64, or  
    echo 3. Visual Studio with C/C++ tools
    echo.
    echo For MSYS2 installation:
    echo 1. Download from https://www.msys2.org/
    echo 2. Install and run: pacman -S gcc make
    echo 3. Add MSYS2 bin directory to your PATH
    echo.
    pause
    exit /b 1
)

REM Create build directory
if not exist build mkdir build

echo Compiling source files with static linking...

REM Compile with static linking for Windows to avoid DLL dependencies
gcc -Wall -Wextra -std=c99 -I include -static -static-libgcc src/*.c -o build/yeep.exe

if %errorlevel% == 0 (
    echo.
    echo ✅ Build successful! Executable created at build\yeep.exe
    echo.
    echo Usage:
    echo   build\yeep.exe                 - Start interactive shell
    echo   build\yeep.exe script.yeep     - Run a Yeep script file
    echo   build\yeep.exe --version       - Show version information
    echo   build\yeep.exe --help          - Show help information
    echo.
    echo Try running: build\yeep.exe examples\hello.yeep
    echo.
    echo To install system-wide, run: install.bat
) else (
    echo.
    echo ❌ Build failed! Please check for errors above.
    pause
    exit /b 1
)
