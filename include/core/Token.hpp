#pragma once

#include <string>
#include <variant>

namespace yeep {
      enum class TokenType {
        // Literals
        NUMBER,
        STRING,
        BOOLEAN,
        IDENTIFIER,
        
        // Operators
        PLUS,
        MINUS,
        MULTIPLY,
        DIVIDE,
        MODULO,
        ASSIGN,
        
        // Comparison
        EQUAL,
        NOT_EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
        
        // Logical
        AND,
        OR,
        NOT,
        
        // Keywords
        LET,           // Added missing LET keyword
        FUN,           // Added missing FUN keyword
        PRINT,
        IF,
        ELSE,
        WHILE,
        FOR,
        FUNCTION,
        RETURN,
        TRUE,
        FALSE,
        
        // Punctuation
        SEMICOLON,
        COMMA,
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        
        // Special
        NEWLINE,
        EOF_TOKEN,
        INVALID
    };
      // Value type for tokens - using variant for type-safe values
    class TokenValue {
    public:
        TokenValue() : value_(nullptr) {} // Nil/null value
        TokenValue(int i) : value_(i) {}
        TokenValue(double d) : value_(d) {}
        TokenValue(const std::string& s) : value_(s) {}
        TokenValue(bool b) : value_(b) {}
        
        bool isNil() const { return std::holds_alternative<std::nullptr_t>(value_); }
        bool isInt() const { return std::holds_alternative<int>(value_); }
        bool isDouble() const { return std::holds_alternative<double>(value_); }
        bool isNumber() const { return isInt() || isDouble(); }
        bool isString() const { return std::holds_alternative<std::string>(value_); }
        bool isBool() const { return std::holds_alternative<bool>(value_); }
        
        int getInt() const { return std::get<int>(value_); }
        double getDouble() const { 
            if (isInt()) return static_cast<double>(getInt());
            return std::get<double>(value_); 
        }
        const std::string& getString() const { return std::get<std::string>(value_); }
        bool getBool() const { return std::get<bool>(value_); }
        
        std::string toString() const {
            if (isNil()) return "nil";
            if (isBool()) return getBool() ? "true" : "false";
            if (isString()) return getString();
            if (isInt()) return std::to_string(getInt());
            if (isDouble()) return std::to_string(getDouble());
            return "unknown";
        }
        
    private:
        std::variant<std::nullptr_t, int, double, std::string, bool> value_;
    };
    
    class Token {
    public:
        Token();
        Token(TokenType type, const std::string& lexeme, int line = 1, int column = 1);
        Token(TokenType type, const std::string& lexeme, const TokenValue& value, int line = 1, int column = 1);
        
        // Getters
        TokenType getType() const { return type_; }
        const std::string& getLexeme() const { return lexeme_; }
        const TokenValue& getValue() const { return value_; }
        int getLine() const { return line_; }
        int getColumn() const { return column_; }
        
        // Utility methods
        bool isType(TokenType type) const { return type_ == type; }
        bool isOneOf(std::initializer_list<TokenType> types) const;
        std::string toString() const;
        
        // Value extraction helpers
        double getNumber() const;
        std::string getString() const;
        bool getBoolean() const;
        
        // Static helpers
        static std::string typeToString(TokenType type);
        static bool isKeyword(const std::string& lexeme);
        static TokenType getKeywordType(const std::string& lexeme);
        
    private:
        TokenType type_;
        std::string lexeme_;
        TokenValue value_;
        int line_;
        int column_;
    };
}
