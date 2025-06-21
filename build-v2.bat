@echo off
echo ========================================
echo Building Yeep Programming Language v2.0
echo Clean Implementation with Built-in Functions
echo ========================================
echo.

REM Create build directory
if not exist build mkdir build

REM Compile all source files
echo [1/5] Compiling Token.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\Token.cpp -o build\Token.o
if errorlevel 1 goto error

echo [2/5] Compiling Lexer.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\Lexer.cpp -o build\Lexer.o
if errorlevel 1 goto error

echo [3/5] Compiling BuiltinFunctions.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\BuiltinFunctions.cpp -o build\BuiltinFunctions.o
if errorlevel 1 goto error

echo [4/5] Compiling Interpreter.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\Interpreter.cpp -o build\Interpreter.o
if errorlevel 1 goto error

echo [5/5] Compiling main.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\main.cpp -o build\main.o
if errorlevel 1 goto error

echo [6/6] Linking executable...
g++ build\Token.o build\Lexer.o build\BuiltinFunctions.o build\Interpreter.o build\main.o -o build\yeep.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo BUILD SUCCESSFUL! ✅
echo ========================================
echo Executable: build\yeep.exe
echo.
echo Test with built-in functions:
echo   build\yeep.exe test_simple.yeep
echo.
pause
exit /b 0

:error
echo.
echo ========================================
echo BUILD FAILED! ❌
echo ========================================
echo Please check compilation errors above.
echo.
pause
exit /b 1
