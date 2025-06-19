@echo off
REM Official Yeep C++ Build Script - WORKING VERSION
echo ========================================
echo Building Yeep Programming Language
echo C++ Version 2.0.0 - OFFICIAL RELEASE
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
