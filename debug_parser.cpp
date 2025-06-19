#include "core/Lexer.hpp"
#include <iostream>

int main() {
    std::string source = "print(\"hello\");";
    
    try {
        yeep::Lexer lexer(source);
        auto tokens = lexer.tokenize();
        
        std::cout << "Tokens generated: " << tokens.size() << std::endl;
        for (size_t i = 0; i < tokens.size(); ++i) {
            std::cout << "Token " << i << ": " << static_cast<int>(tokens[i].getType()) 
                      << " '" << tokens[i].getLexeme() << "'" << std::endl;
        }
        
        return 0;
        
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
