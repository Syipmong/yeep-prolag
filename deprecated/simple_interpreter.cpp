// Simple working interpreter for print statements
#include "core/Lexer.hpp"
#include "core/Token.hpp"
#include <iostream>
#include <string>

bool isStringLiteral(const yeep::Token& token) {
    return token.getType() == yeep::TokenType::STRING;
}

void executePrint(const std::vector<yeep::Token>& tokens, size_t& pos) {
    // Expect: print ( "string" ) ;
    if (pos + 4 < tokens.size() && 
        tokens[pos].getType() == yeep::TokenType::PRINT &&
        tokens[pos + 1].getType() == yeep::TokenType::LEFT_PAREN &&
        isStringLiteral(tokens[pos + 2]) &&
        tokens[pos + 3].getType() == yeep::TokenType::RIGHT_PAREN &&
        tokens[pos + 4].getType() == yeep::TokenType::SEMICOLON) {
        
        std::string value = tokens[pos + 2].getLexeme();
        std::cout << value << std::endl;
        pos += 5; // Move past the print statement
    } else {
        std::cout << "Error: Invalid print statement syntax" << std::endl;
        pos = tokens.size(); // Skip to end
    }
}

void simpleInterpret(const std::vector<yeep::Token>& tokens) {
    for (size_t pos = 0; pos < tokens.size(); ) {
        if (tokens[pos].getType() == yeep::TokenType::PRINT) {
            executePrint(tokens, pos);
        } else if (tokens[pos].getType() == yeep::TokenType::EOF_TOKEN) {
            break;
        } else {
            pos++; // Skip unknown tokens
        }
    }
}

int main() {
    std::string source = "print(\"Hello, World!\");";
    std::cout << "Yeep Simple Interpreter Test" << std::endl;
    std::cout << "Source: " << source << std::endl;
    
    yeep::Lexer lexer(source);
    auto tokens = lexer.tokenize();
    
    std::cout << "Tokens: " << tokens.size() << std::endl;
    simpleInterpret(tokens);
    
    return 0;
}
