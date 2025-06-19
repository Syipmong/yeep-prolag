#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Forward declarations
namespace yeep {
    class Token;
    class Lexer;
    class Parser;
    class Interpreter;
    class Expression;
    class SymbolTable;
    class ErrorHandler;
}

// Include core components
#include "core/Token.hpp"
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/Interpreter.hpp"
#include "ast/Expression.hpp"
#include "utils/SymbolTable.hpp"
#include "utils/ErrorHandler.hpp"

namespace yeep {
    // Version information
    constexpr const char* VERSION = "1.2.0";
    constexpr const char* COPYRIGHT = "Copyright (c) 2025 Syipmong";
    constexpr const char* LICENSE = "Licensed under MIT License";
    
    // Runtime configuration
    struct Config {
        bool interactive_mode = false;
        bool debug_mode = false;
        std::string script_file;
        std::vector<std::string> args;
    };
    
    // Main interpreter engine
    class YeepEngine {
    public:
        YeepEngine();
        ~YeepEngine();
        
        // Main execution methods
        int run(const Config& config);
        int executeFile(const std::string& filename);
        int runInteractive();
        
        // Utility methods
        void printVersion() const;
        void printHelp(const std::string& program_name) const;
      private:
        // Internal execution methods
        int executeSource(const std::string& source, bool interactive = false);
        void printInteractiveHelp() const;
        void simpleInterpret(const std::vector<Token>& tokens);
        void executePrintStatement(const std::vector<Token>& tokens, size_t& pos);
        
        // Components
        std::unique_ptr<Lexer> lexer_;
        std::unique_ptr<Parser> parser_;
        std::unique_ptr<Interpreter> interpreter_;
        std::unique_ptr<ErrorHandler> error_handler_;
    };
}

// Compatibility macros for easier migration
#define YEEP_VERSION yeep::VERSION
