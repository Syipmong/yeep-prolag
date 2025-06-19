#include "utils/SymbolTable.hpp"
#include <stdexcept>

namespace yeep {
    
    SymbolTable::SymbolTable() {}
    
    void SymbolTable::define(const std::string& name, const TokenValue& value) {
        symbols_[name] = value;
    }
    
    TokenValue SymbolTable::get(const std::string& name) {
        auto it = symbols_.find(name);
        if (it != symbols_.end()) {
            return it->second;
        }
        throw std::runtime_error("Undefined variable: " + name);
    }
    
    void SymbolTable::assign(const std::string& name, const TokenValue& value) {
        auto it = symbols_.find(name);
        if (it != symbols_.end()) {
            it->second = value;
        } else {
            throw std::runtime_error("Undefined variable: " + name);
        }
    }
    
    bool SymbolTable::isDefined(const std::string& name) const {
        return symbols_.find(name) != symbols_.end();
    }
    
    void SymbolTable::enterScope() {
        // TODO: Implement scope management
    }
    
    void SymbolTable::exitScope() {
        // TODO: Implement scope management
    }
    
} // namespace yeep
