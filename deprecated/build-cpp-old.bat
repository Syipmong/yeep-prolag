@echo off
REM Build script for Yeep Programming Language (C++ Version)
REM This script compiles the C++ version of Yeep with proper error handling

echo Building Yeep Programming Language (C++ Version)...
echo.

REM Create build directory if it doesn't exist
if not exist "build" mkdir build
if not exist "build\core" mkdir build\core
if not exist "build\ast" mkdir build\ast
if not exist "build\utils" mkdir build\utils

REM Set compiler flags
set CXX=g++
set CXXFLAGS=-Wall -Wextra -std=c++17 -I include

REM Check if g++ is available
where g++ >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found in PATH
    echo Please install MinGW-w64 or Visual Studio Build Tools
    echo You can install MinGW-w64 from: https://www.mingw-w64.org/
    pause
    exit /b 1
)

echo Compiling C++ source files...

REM Compile core files
echo - Compiling Token.cpp...
%CXX% %CXXFLAGS% -c src\core\Token.cpp -o build\core\Token.o
if %errorlevel% neq 0 goto error

echo - Compiling Lexer.cpp...
%CXX% %CXXFLAGS% -c src\core\Lexer.cpp -o build\core\Lexer.o
if %errorlevel% neq 0 goto error

echo - Compiling Parser.cpp...
%CXX% %CXXFLAGS% -c src\core\Parser.cpp -o build\core\Parser.o
if %errorlevel% neq 0 goto error

echo - Compiling Interpreter.cpp...
%CXX% %CXXFLAGS% -c src\core\Interpreter.cpp -o build\core\Interpreter.o
if %errorlevel% neq 0 goto error

REM Compile AST files
echo - Compiling Expression.cpp...
%CXX% %CXXFLAGS% -c src\ast\Expression.cpp -o build\ast\Expression.o
if %errorlevel% neq 0 goto error

REM Compile main file
echo - Compiling main.cpp...
%CXX% %CXXFLAGS% -c src\main.cpp -o build\main.o
if %errorlevel% neq 0 goto error

REM Link the executable
echo - Linking executable...
%CXX% build\main.o build\core\Token.o build\core\Lexer.o build\core\Parser.o build\core\Interpreter.o build\ast\Expression.o -o build\yeep.exe
if %errorlevel% neq 0 goto error

echo.
echo ✓ Build successful!
echo Executable created: build\yeep.exe
echo.
echo To test the build:
echo   build\yeep.exe                 - Start interactive REPL
echo   build\yeep.exe examples\test.yeep - Run a script file
echo.

REM Test the executable
echo Testing the executable...
build\yeep.exe --version 2>nul
if %errorlevel% neq 0 (
    echo Testing with help command...
    echo help | build\yeep.exe
)

goto end

:error
echo.
echo ✗ Build failed!
echo Check the error messages above for details.
echo.
echo Common issues:
echo - Missing g++ compiler ^(install MinGW-w64^)
echo - Missing include files ^(check include directory^)
echo - Syntax errors in source code
echo.
pause
exit /b 1

:end
echo.
echo Build completed successfully!
pause
