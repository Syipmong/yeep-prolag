#include "yeep.hpp"
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/Interpreter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace yeep {
    
    YeepEngine::YeepEngine() 
        : lexer_(nullptr), parser_(nullptr), interpreter_(std::make_unique<Interpreter>()), error_handler_(nullptr) {
    }
    
    YeepEngine::~YeepEngine() = default;
    
    int YeepEngine::run(const Config& config) {
        if (!config.script_file.empty()) {
            return executeFile(config.script_file);
        } else {
            return runInteractive();
        }
    }
    
    int YeepEngine::executeFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
            return 74; // I/O error
        }
        
        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string source = buffer.str();
        file.close();
        
        return executeSource(source);
    }
    
    int YeepEngine::runInteractive() {
        std::cout << "Yeep Programming Language v" << VERSION << std::endl;
        std::cout << "Type 'exit' to quit, 'help' for help" << std::endl;
        
        std::string line;
        while (true) {
            std::cout << "yeep> ";
            
            if (!std::getline(std::cin, line)) {
                std::cout << std::endl;
                break;
            }
            
            // Handle special commands
            if (line == "exit" || line == "quit") {
                break;
            } else if (line == "help") {
                printInteractiveHelp();
                continue;
            } else if (line == "version") {
                printVersion();
                continue;
            } else if (line == "clear") {
                // Clear interpreter state
                interpreter_ = std::make_unique<Interpreter>();
                std::cout << "Interpreter state cleared." << std::endl;
                continue;
            } else if (line.empty()) {
                continue;
            }
            
            // Execute the line (don't exit on error in interactive mode)
            executeSource(line, true);
        }
        
        return 0;
    }
    
    void YeepEngine::printVersion() const {
        std::cout << "Yeep Programming Language v" << VERSION << std::endl;
        std::cout << "Copyright (c) 2025 Syipmong" << std::endl;
        std::cout << "Licensed under MIT License" << std::endl;
        std::cout << "Built with C++ " << __cplusplus << std::endl;
    }
    
    void YeepEngine::printHelp(const std::string& program_name) const {
        std::cout << "Yeep Programming Language v" << VERSION << std::endl << std::endl;
        std::cout << "Usage: " << program_name << " [options] [script]" << std::endl << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help     Show this help message" << std::endl;
        std::cout << "  -v, --version  Show version information" << std::endl;
        std::cout << "  -i, --repl     Force interactive mode (REPL)" << std::endl;
        std::cout << std::endl;
        std::cout << "Examples:" << std::endl;
        std::cout << "  " << program_name << "                    Start interactive shell" << std::endl;
        std::cout << "  " << program_name << " script.yeep        Run a Yeep script" << std::endl;
        std::cout << "  " << program_name << " -i                 Force interactive mode" << std::endl;
        std::cout << "  " << program_name << " --version          Show version" << std::endl;
    }
    
    int YeepEngine::executeSource(const std::string& source, bool interactive) {
        try {
            // Lexical analysis
            Lexer lexer(source);
            std::vector<Token> tokens = lexer.tokenize();
            
            // Syntax analysis
            Parser parser(tokens);
            auto statements = parser.parse();
            
            if (parser.hadError()) {
                return interactive ? 0 : 65; // Syntax error
            }
            
            // Interpretation
            interpreter_->interpret(statements);
            
            if (interpreter_->hadRuntimeError()) {
                return interactive ? 0 : 70; // Runtime error
            }
            
            return 0;
            
        } catch (const LexerError& e) {
            std::cerr << "Lexer error at line " << e.getLine() 
                      << ", column " << e.getColumn() << ": " << e.what() << std::endl;
            return interactive ? 0 : 65;
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            return interactive ? 0 : 1;
        }
    }
    
    void YeepEngine::printInteractiveHelp() const {
        std::cout << std::endl;
        std::cout << "Yeep Programming Language Help" << std::endl;
        std::cout << "==============================" << std::endl;
        std::cout << std::endl;
        std::cout << "Commands:" << std::endl;
        std::cout << "  exit, quit  - Exit the REPL" << std::endl;
        std::cout << "  help        - Show this help message" << std::endl;
        std::cout << "  version     - Show version information" << std::endl;
        std::cout << "  clear       - Clear interpreter state" << std::endl;
        std::cout << std::endl;
        std::cout << "Language Features:" << std::endl;
        std::cout << "  Variables:   let x = 5;" << std::endl;
        std::cout << "  Arithmetic:  x + 2, x * 3, x / 2" << std::endl;
        std::cout << "  Comparison:  x > 5, x == 10, x != 0" << std::endl;
        std::cout << "  Booleans:    true, false, !true" << std::endl;
        std::cout << "  Strings:     \"Hello, World!\"" << std::endl;
        std::cout << "  Printing:    print(x);" << std::endl;
        std::cout << "  Blocks:      { let y = 2; print(y); }" << std::endl;
        std::cout << "  Conditions:  if (x > 0) { print(\"positive\"); }" << std::endl;
        std::cout << "  Loops:       while (x > 0) { print(x); x = x - 1; }" << std::endl;
        std::cout << std::endl;
        std::cout << "Examples:" << std::endl;
        std::cout << "  let name = \"Alice\";" << std::endl;
        std::cout << "  print(\"Hello, \" + name);" << std::endl;
        std::cout << "  let count = 10;" << std::endl;
        std::cout << "  while (count > 0) { print(count); count = count - 1; }" << std::endl;
        std::cout << std::endl;
    }
    
} // namespace yeep
