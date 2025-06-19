#pragma once

#include <string>
#include <stdexcept>

namespace yeep {
    
    class ErrorHandler {
    public:
        static void reportError(const std::string& message);
        static void reportError(const std::string& message, int line, int column);
        static void reportWarning(const std::string& message);
        static void reportWarning(const std::string& message, int line, int column);
        
        static bool hasErrors();
        static void clearErrors();
        
    private:
        static bool hasErrors_;
    };
    
} // namespace yeep
