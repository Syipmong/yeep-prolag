@echo off
REM Full Yeep C++ Build Script with Complete Parser/Interpreter
echo ========================================
echo Building Yeep Programming Language
echo C++ Version with Full Parser/Interpreter
echo ========================================

REM Create build directories
if not exist build mkdir build
if not exist build\core mkdir build\core
if not exist build\ast mkdir build\ast
if not exist build\utils mkdir build\utils

echo.
echo [1/8] Compiling Token.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Token.cpp -o build\core\Token.o
if errorlevel 1 goto error

echo [2/8] Compiling Lexer.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Lexer.cpp -o build\core\Lexer.o
if errorlevel 1 goto error

echo [3/8] Compiling Expression.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\ast\Expression.cpp -o build\ast\Expression.o
if errorlevel 1 goto error

echo [4/8] Compiling Parser.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Parser.cpp -o build\core\Parser.o
if errorlevel 1 goto error

echo [5/8] Compiling BuiltinFunctions.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\BuiltinFunctions.cpp -o build\core\BuiltinFunctions.o
if errorlevel 1 goto error

echo [6/8] Compiling Interpreter.cpp...
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Interpreter.cpp -o build\core\Interpreter.o
if errorlevel 1 goto error

echo [7/8] Creating main with full interpreter...
echo #include ^<iostream^> > build\main_full.cpp
echo #include ^<fstream^> >> build\main_full.cpp
echo #include ^<sstream^> >> build\main_full.cpp
echo #include "core/Lexer.hpp" >> build\main_full.cpp
echo #include "core/Parser.hpp" >> build\main_full.cpp
echo #include "core/Interpreter.hpp" >> build\main_full.cpp
echo. >> build\main_full.cpp
echo int main(int argc, char* argv[]) { >> build\main_full.cpp
echo   if (argc ^!= 2) { >> build\main_full.cpp
echo     std::cout ^<^< "Usage: yeep ^<filename^>" ^<^< std::endl; >> build\main_full.cpp
echo     return 1; >> build\main_full.cpp
echo   } >> build\main_full.cpp
echo. >> build\main_full.cpp
echo   std::ifstream file(argv[1]); >> build\main_full.cpp
echo   if (!file.is_open()) { >> build\main_full.cpp
echo     std::cerr ^<^< "Could not open file: " ^<^< argv[1] ^<^< std::endl; >> build\main_full.cpp
echo     return 1; >> build\main_full.cpp
echo   } >> build\main_full.cpp
echo. >> build\main_full.cpp
echo   std::string source((std::istreambuf_iterator^<char^>(file)), std::istreambuf_iterator^<char^>()); >> build\main_full.cpp
echo   file.close(); >> build\main_full.cpp
echo. >> build\main_full.cpp
echo   try { >> build\main_full.cpp
echo     yeep::Lexer lexer(source); >> build\main_full.cpp
echo     auto tokens = lexer.tokenize(); >> build\main_full.cpp
echo     yeep::Parser parser(tokens); >> build\main_full.cpp
echo     auto statements = parser.parse(); >> build\main_full.cpp
echo     yeep::Interpreter interpreter; >> build\main_full.cpp
echo     interpreter.interpret(statements); >> build\main_full.cpp
echo   } catch (const std::exception^& e) { >> build\main_full.cpp
echo     std::cerr ^<^< "Error: " ^<^< e.what() ^<^< std::endl; >> build\main_full.cpp
echo     return 1; >> build\main_full.cpp
echo   } >> build\main_full.cpp
echo   return 0; >> build\main_full.cpp
echo } >> build\main_full.cpp

g++ -Wall -Wextra -std=c++17 -I include -c build\main_full.cpp -o build\main_full.o
if errorlevel 1 goto error

echo [8/8] Linking full interpreter executable...
g++ build\main_full.o build\core\Token.o build\core\Lexer.o build\ast\Expression.o build\core\Parser.o build\core\BuiltinFunctions.o build\core\Interpreter.o -o build\yeep_full.exe
if errorlevel 1 goto error

echo.
echo ========================================
echo BUILD SUCCESSFUL! ✅
echo ========================================
echo Full interpreter executable: build\yeep_full.exe
echo.
pause
exit /b 0

:error
echo.
echo ========================================
echo BUILD FAILED! ❌
echo ========================================
echo Please ensure you have:
echo 1. MSYS2 with GCC, or
echo 2. MinGW-w64, or  
echo 3. Visual Studio with C/C++ tools
echo.
pause
exit /b 1
