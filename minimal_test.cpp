// Minimal test version
#include "core/Lexer.hpp"
#include "core/Token.hpp"
#include <iostream>

int main() {
    std::string source = "print(\"hello\");";
    std::cout << "Testing: " << source << std::endl;
    
    yeep::Lexer lexer(source);
    auto tokens = lexer.tokenize();
    
    std::cout << "Success! Generated " << tokens.size() << " tokens" << std::endl;
    std::cout << "Hello world from Yeep lexer!" << std::endl;
    
    return 0;
}
