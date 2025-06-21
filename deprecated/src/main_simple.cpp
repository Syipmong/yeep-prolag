#include "yeep.hpp"
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/Interpreter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// Simple main function that uses the YeepEngine from the header
int main(int argc, char* argv[]) {
    try {
        yeep::YeepEngine engine;
        
        if (argc > 2) {
            std::cout << "Usage: yeep [script]" << std::endl;
            return 64;
        } else if (argc == 2) {
            return engine.executeFile(argv[1]);
        } else {
            return engine.runInteractive();
        }
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}
