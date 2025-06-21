#pragma once

#include "core/Token.hpp"
#include <vector>
#include <functional>
#include <map>
#include <string>

namespace yeep {
    
    // Built-in function signature
    using BuiltinFunction = std::function<TokenValue(const std::vector<TokenValue>&)>;
    
    class BuiltinFunctions {
    public:
        static void initialize();
        static bool isBuiltin(const std::string& name);
        static BuiltinFunction getBuiltin(const std::string& name);
        static std::vector<std::string> getAllFunctionNames();
        
    private:
        static std::map<std::string, BuiltinFunction> functions_;
        static bool initialized_;
        
        // Mathematical functions
        static TokenValue abs(const std::vector<TokenValue>& args);
        static TokenValue sqrt(const std::vector<TokenValue>& args);
        static TokenValue pow(const std::vector<TokenValue>& args);
        static TokenValue max(const std::vector<TokenValue>& args);
        static TokenValue min(const std::vector<TokenValue>& args);
        static TokenValue floor(const std::vector<TokenValue>& args);
        static TokenValue ceil(const std::vector<TokenValue>& args);
        static TokenValue round(const std::vector<TokenValue>& args);
        
        // String functions
        static TokenValue length(const std::vector<TokenValue>& args);
        static TokenValue substring(const std::vector<TokenValue>& args);
        static TokenValue uppercase(const std::vector<TokenValue>& args);
        static TokenValue lowercase(const std::vector<TokenValue>& args);
        static TokenValue contains(const std::vector<TokenValue>& args);
        static TokenValue startsWith(const std::vector<TokenValue>& args);
        static TokenValue endsWith(const std::vector<TokenValue>& args);
        
        // Type conversion functions
        static TokenValue toString(const std::vector<TokenValue>& args);
        static TokenValue toNumber(const std::vector<TokenValue>& args);
        static TokenValue toBoolean(const std::vector<TokenValue>& args);
        
        // Utility functions
        static TokenValue type(const std::vector<TokenValue>& args);
        static TokenValue input(const std::vector<TokenValue>& args);
        static TokenValue random(const std::vector<TokenValue>& args);
        static TokenValue time(const std::vector<TokenValue>& args);
        
        // Helper functions
        static void validateArgCount(const std::vector<TokenValue>& args, size_t expected, const std::string& functionName);
        static void validateArgCount(const std::vector<TokenValue>& args, size_t min, size_t max, const std::string& functionName);
    };
    
} // namespace yeep
