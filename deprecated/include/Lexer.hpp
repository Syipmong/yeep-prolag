#pragma once

#include "Token.hpp"
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

namespace yeep {
    
    class LexerError : public std::runtime_error {
    public:
        LexerError(const std::string& message, int line, int column)
            : std::runtime_error(message), line_(line), column_(column) {}
        
        int getLine() const { return line_; }
        int getColumn() const { return column_; }
        
    private:
        int line_;
        int column_;
    };
    
    class Lexer {
    public:
        explicit Lexer(const std::string& source);
        ~Lexer() = default;
        
        // Main tokenization methods
        std::vector<Token> tokenize();
        Token nextToken();
        
        // State methods
        bool hasMore() const;
        void reset();
        
        // Error handling
        bool hasErrors() const { return !errors_.empty(); }
        const std::vector<std::string>& getErrors() const { return errors_; }
        
    private:
        // Source management
        std::string source_;
        size_t current_;
        int line_;
        int column_;
        int start_column_;
        
        // Error tracking
        std::vector<std::string> errors_;
        
        // Character processing
        char advance();
        char peek() const;
        char peekNext() const;
        bool match(char expected);
        bool isAtEnd() const;
        
        // Token creation
        Token makeToken(TokenType type);
        Token makeToken(TokenType type, const TokenValue& value);
        void addError(const std::string& message);
          // Specific token parsing
        Token scanString(int line, int column);
        Token scanNumber(int line, int column);
        Token scanIdentifier(int line, int column);
        Token scanComment();
        
        // Whitespace handling
        void skipWhitespace();
        
        // Character classification
        bool isDigit(char c) const;
        bool isAlpha(char c) const;
        bool isAlphaNumeric(char c) const;
        bool isWhitespace(char c) const;
        
        // Position tracking
        void newLine();
        std::string getCurrentLexeme() const;
    };
}
