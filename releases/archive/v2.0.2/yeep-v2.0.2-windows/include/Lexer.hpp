#pragma once

#include "Token.hpp"
#include <vector>
#include <string>

namespace yeep {

    class Lexer {
    public:
        explicit Lexer(const std::string& source);
        std::vector<Token> tokenize();
        
    private:
        std::string source_;
        size_t current_;
        int line_;
        
        bool isAtEnd() const;
        char advance();
        char peek() const;
        char peekNext() const;
        bool match(char expected);
        
        void skipWhitespace();
        void skipComment();
        
        Token makeToken(TokenType type) const;
        Token makeToken(TokenType type, const Value& value) const;
        Token errorToken(const std::string& message) const;
        
        Token string();
        Token number();
        Token identifier();
        
        TokenType identifierType() const;
        TokenType checkKeyword(size_t start, const std::string& rest, TokenType type) const;
    };

} // namespace yeep
