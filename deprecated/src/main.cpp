#include <iostream>
#include <fstream>
#include <sstream>
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/Interpreter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: yeep <filename>" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    try {
        yeep::Lexer lexer(source);
        auto tokens = lexer.tokenize();
        yeep::Parser parser(tokens);
        auto statements = parser.parse();
        yeep::Interpreter interpreter;
        interpreter.interpret(statements);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
