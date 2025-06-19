#include "utils/ErrorHandler.hpp"
#include <iostream>

namespace yeep {
    
    bool ErrorHandler::hasErrors_ = false;
    
    void ErrorHandler::reportError(const std::string& message) {
        std::cerr << "Error: " << message << std::endl;
        hasErrors_ = true;
    }
    
    void ErrorHandler::reportError(const std::string& message, int line, int column) {
        std::cerr << "Error at line " << line << ", column " << column << ": " << message << std::endl;
        hasErrors_ = true;
    }
    
    void ErrorHandler::reportWarning(const std::string& message) {
        std::cerr << "Warning: " << message << std::endl;
    }
    
    void ErrorHandler::reportWarning(const std::string& message, int line, int column) {
        std::cerr << "Warning at line " << line << ", column " << column << ": " << message << std::endl;
    }
    
    bool ErrorHandler::hasErrors() {
        return hasErrors_;
    }
    
    void ErrorHandler::clearErrors() {
        hasErrors_ = false;
    }
    
} // namespace yeep
