@echo off
echo Building full Yeep interpreter...

REM Create build directories
if not exist build mkdir build
if not exist build\core mkdir build\core
if not exist build\ast mkdir build\ast

REM Compile all the necessary files
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Token.cpp -o build\core\Token.o
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Lexer.cpp -o build\core\Lexer.o
g++ -Wall -Wextra -std=c++17 -I include -c src\ast\Expression.cpp -o build\ast\Expression.o
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Parser.cpp -o build\core\Parser.o
g++ -Wall -Wextra -std=c++17 -I include -c src\core\BuiltinFunctions.cpp -o build\core\BuiltinFunctions.o
g++ -Wall -Wextra -std=c++17 -I include -c src\core\Interpreter.cpp -o build\core\Interpreter.o
g++ -Wall -Wextra -std=c++17 -I include -c src\main_full.cpp -o build\main_full.o

REM Link the executable
g++ build\main_full.o build\core\Token.o build\core\Lexer.o build\ast\Expression.o build\core\Parser.o build\core\BuiltinFunctions.o build\core\Interpreter.o -o build\yeep_full.exe

echo Build complete!
echo Executable: build\yeep_full.exe
