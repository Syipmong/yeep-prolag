#pragma once

#include "Token.hpp"
#include <vector>
#include <functional>
#include <unordered_map>

namespace yeep {

    using BuiltinFunction = std::function<Value(const std::vector<Value>&)>;

    class BuiltinFunctions {
    public:
        static void initialize();
        static bool isBuiltin(const std::string& name);
        static Value call(const std::string& name, const std::vector<Value>& args);
        
    private:
        static std::unordered_map<std::string, BuiltinFunction> functions_;
        static bool initialized_;
        
        // Math functions
        static Value abs(const std::vector<Value>& args);
        static Value sqrt(const std::vector<Value>& args);
        static Value pow(const std::vector<Value>& args);
        static Value max(const std::vector<Value>& args);
        static Value min(const std::vector<Value>& args);
        static Value floor(const std::vector<Value>& args);
        static Value ceil(const std::vector<Value>& args);
        static Value round(const std::vector<Value>& args);
        static Value random(const std::vector<Value>& args);
        
        // String functions
        static Value length(const std::vector<Value>& args);
        static Value substring(const std::vector<Value>& args);
        static Value uppercase(const std::vector<Value>& args);
        static Value lowercase(const std::vector<Value>& args);
        static Value contains(const std::vector<Value>& args);
        
        // Type functions
        static Value type(const std::vector<Value>& args);
        static Value toString(const std::vector<Value>& args);
        static Value toNumber(const std::vector<Value>& args);
        
        // I/O functions
        static Value input(const std::vector<Value>& args);
        
        // Utility
        static void checkArgCount(const std::vector<Value>& args, size_t expected, const std::string& name);
    };

} // namespace yeep
