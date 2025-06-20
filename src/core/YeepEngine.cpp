#include "yeep.hpp"
#include "core/Lexer.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

namespace yeep {
    
    YeepEngine::YeepEngine() 
        : lexer_(nullptr), parser_(nullptr), interpreter_(nullptr), error_handler_(nullptr) {
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
            } else if (line.empty()) {
                continue;
            }
            
            // Execute the line
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
    }    int YeepEngine::executeSource(const std::string& source, bool interactive) {
        try {
            // Lexical analysis
            Lexer lexer(source);
            std::vector<Token> tokens = lexer.tokenize();
            
            if (tokens.empty()) {
                return 0; // Empty source
            }
            
            // Simple interpretation for basic functionality
            simpleInterpret(tokens);
            
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
    
    void YeepEngine::simpleInterpret(const std::vector<Token>& tokens) {
        for (size_t pos = 0; pos < tokens.size(); ) {
            if (tokens[pos].getType() == TokenType::PRINT) {
                executePrintStatement(tokens, pos);
            } else if (tokens[pos].getType() == TokenType::EOF_TOKEN) {
                break;
            } else {
                pos++; // Skip unknown tokens
            }
        }
    }
    
    void YeepEngine::executePrintStatement(const std::vector<Token>& tokens, size_t& pos) {
        // Expect: print ( "string" ) ;
        if (pos + 4 < tokens.size() && 
            tokens[pos].getType() == TokenType::PRINT &&
            tokens[pos + 1].getType() == TokenType::LEFT_PAREN &&
            tokens[pos + 2].getType() == TokenType::STRING &&
            tokens[pos + 3].getType() == TokenType::RIGHT_PAREN &&
            tokens[pos + 4].getType() == TokenType::SEMICOLON) {
            
            std::string value = tokens[pos + 2].getLexeme();
            std::cout << value << std::endl;
            pos += 5; // Move past the print statement
        } else {
            std::cerr << "Error: Invalid print statement syntax" << std::endl;
            pos = tokens.size(); // Skip to end
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
        std::cout << std::endl;
        std::cout << "Language Features (Currently Supported):" << std::endl;
        std::cout << "  Print:       print(\"Hello, World!\");" << std::endl;
        std::cout << std::endl;
        std::cout << "Examples:" << std::endl;
        std::cout << "  print(\"Hello, World!\");" << std::endl;
        std::cout << "  print(\"Welcome to Yeep!\");" << std::endl;
        std::cout << std::endl;
    }
    
} // namespace yeep
