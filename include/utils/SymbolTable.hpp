#pragma once

#include "core/Token.hpp"
#include <unordered_map>
#include <string>

namespace yeep {
    
    class SymbolTable {
    public:
        SymbolTable();
        ~SymbolTable() = default;
        
        void define(const std::string& name, const TokenValue& value);
        TokenValue get(const std::string& name);
        void assign(const std::string& name, const TokenValue& value);
        bool isDefined(const std::string& name) const;
        
        void enterScope();
        void exitScope();
        
    private:
        std::unordered_map<std::string, TokenValue> symbols_;
    };
    
} // namespace yeep
