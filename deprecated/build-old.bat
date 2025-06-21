@echo off
echo ========================================
echo Building Yeep Programming Language
echo C++ Version with Full Features
echo ========================================
echo.

REM Create build directories
if not exist build mkdir build
if not exist build\core mkdir build\core
if not exist build\ast mkdir build\ast

REM Compile core components
echo [1/7] Compiling Token.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Token.cpp -o build\core\Token.o
if errorlevel 1 goto error

echo [2/7] Compiling Lexer.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Lexer.cpp -o build\core\Lexer.o
if errorlevel 1 goto error

echo [3/7] Compiling Parser.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Parser.cpp -o build\core\Parser.o
if errorlevel 1 goto error

echo [4/7] Compiling Expression.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\ast\Expression.cpp -o build\ast\Expression.o
if errorlevel 1 goto error

echo [5/7] Compiling BuiltinFunctions.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\BuiltinFunctions.cpp -o build\core\BuiltinFunctions.o
if errorlevel 1 goto error

echo [6/7] Compiling Interpreter.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Interpreter.cpp -o build\core\Interpreter.o
if errorlevel 1 goto error

echo [7/7] Compiling main.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\main.cpp -o build\main.o
if errorlevel 1 goto error

echo [8/8] Linking executable...
g++ build\main.o build\core\Token.o build\core\Lexer.o build\core\Parser.o build\ast\Expression.o build\core\BuiltinFunctions.o build\core\Interpreter.o -o build\yeep.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo BUILD SUCCESSFUL! ✅
echo ========================================
echo Executable: build\yeep.exe
echo.
echo Ready to run Yeep programs with full built-in function support!
echo Try: build\yeep.exe examples\hello.yeep
echo.
pause
exit /b 0

:error
echo.
echo ========================================
echo BUILD FAILED! ❌
echo ========================================
echo Please ensure you have a C++17 compatible compiler installed.
echo.
pause
exit /b 1
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
