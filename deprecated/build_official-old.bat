@echo off
REM Official Yeep C++ Build Script - WORKING VERSION
echo ========================================
echo Building Yeep Programming Language
echo C++ Version 2.1.0-dev - ENHANCED FEATURES
echo ========================================

REM Create build directories
if not exist build mkdir build
if not exist build\core mkdir build\core
if not exist build\ast mkdir build\ast

echo.
echo [1/9] Compiling main.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\main.cpp -o build\main.o
if errorlevel 1 goto error

echo [2/9] Compiling YeepEngine.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\YeepEngine.cpp -o build\core\YeepEngine.o
if errorlevel 1 goto error

echo [3/9] Compiling Token.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Token.cpp -o build\core\Token.o
if errorlevel 1 goto error

echo [4/9] Compiling Lexer.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Lexer.cpp -o build\core\Lexer.o
if errorlevel 1 goto error

echo [5/9] Compiling BuiltinFunctions.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\BuiltinFunctions.cpp -o build\core\BuiltinFunctions.o
if errorlevel 1 goto error

echo [6/9] Compiling Interpreter.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Interpreter.cpp -o build\core\Interpreter.o
if errorlevel 1 goto error

echo [7/9] Compiling Parser.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Parser.cpp -o build\core\Parser.o
if errorlevel 1 goto error

echo [8/9] Compiling Expression.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\ast\Expression.cpp -o build\ast\Expression.o
if errorlevel 1 goto error

echo [9/9] Linking executable...
g++ build\main.o build\core\YeepEngine.o build\core\Token.o build\core\Lexer.o build\core\BuiltinFunctions.o build\core\Interpreter.o build\core\Parser.o build\ast\Expression.o -o build\yeep.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo BUILD SUCCESSFUL! ✅
echo ========================================
echo.
echo Executable: build\yeep.exe
echo.
echo Test with:
echo   build\yeep.exe              (Interactive mode)
echo   build\yeep.exe demo.yeep    (Run demo script)
echo.

goto end

:error
echo.
echo ========================================
echo BUILD FAILED! ❌
echo ========================================
echo Check the error messages above.
exit /b 1

:end
