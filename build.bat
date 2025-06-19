@echo off
echo Building Yeep Programming Language...
echo.

REM Check if we have gcc available
where gcc >nul 2>&1
if errorlevel 1 (
    echo ERROR: GCC compiler not found!
    echo.
    echo To build Yeep on Windows, you need:
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
