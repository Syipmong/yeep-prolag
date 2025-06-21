#pragma once

#include <string>
#include <variant>
#include <vector>

namespace yeep {

    enum class TokenType {
        // Literals
        NUMBER,
        STRING, 
        TRUE,
        FALSE,
        NIL,
        IDENTIFIER,
        
        // Operators
        PLUS,           // +
        MINUS,          // -
        MULTIPLY,       // *
        DIVIDE,         // /
        MODULO,         // %
        
        // Comparison
        EQUAL,          // ==
        NOT_EQUAL,      // !=
        LESS,           // <
        LESS_EQUAL,     // <=
        GREATER,        // >
        GREATER_EQUAL,  // >=
        
        // Logical
        AND,            // &&
        OR,             // ||
        NOT,            // !
        
        // Assignment
        ASSIGN,         // =
        
        // Punctuation
        LEFT_PAREN,     // (
        RIGHT_PAREN,    // )
        LEFT_BRACE,     // {
        RIGHT_BRACE,    // }
        COMMA,          // ,
        SEMICOLON,      // ;
        
        // Keywords
        LET,
        FUN,
        IF,
        ELSE,
        WHILE,
        FOR,
        RETURN,
        PRINT,
        
        // Special
        NEWLINE,
        EOF_TOKEN,
        INVALID
    };

    // Value type for runtime values
    class Value {
    public:
        Value() : data_(nullptr) {} // nil
        Value(double d) : data_(d) {}
        Value(const std::string& s) : data_(s) {}
        Value(bool b) : data_(b) {}
        
        bool isNil() const { return std::holds_alternative<std::nullptr_t>(data_); }
        bool isNumber() const { return std::holds_alternative<double>(data_); }
        bool isString() const { return std::holds_alternative<std::string>(data_); }
        bool isBool() const { return std::holds_alternative<bool>(data_); }
        
        double getNumber() const { return std::get<double>(data_); }
        const std::string& getString() const { return std::get<std::string>(data_); }
        bool getBool() const { return std::get<bool>(data_); }
        
        std::string toString() const {
            if (isNil()) return "nil";
            if (isBool()) return getBool() ? "true" : "false";
            if (isString()) return getString();
            if (isNumber()) return std::to_string(getNumber());
            return "unknown";
        }
        
        bool isTruthy() const {
            if (isNil()) return false;
            if (isBool()) return getBool();
            if (isNumber()) return getNumber() != 0.0;
            if (isString()) return !getString().empty();
            return true;
        }
        
    private:
        std::variant<std::nullptr_t, double, std::string, bool> data_;
    };

    class Token {
    public:
        Token() : type_(TokenType::INVALID), line_(0) {}
        Token(TokenType type, const std::string& lexeme, int line = 1)
            : type_(type), lexeme_(lexeme), line_(line) {}
        Token(TokenType type, const std::string& lexeme, const Value& value, int line = 1)
            : type_(type), lexeme_(lexeme), value_(value), line_(line) {}
        
        TokenType getType() const { return type_; }
        const std::string& getLexeme() const { return lexeme_; }
        const Value& getValue() const { return value_; }
        int getLine() const { return line_; }
        
        static std::string typeToString(TokenType type);
        
    private:
        TokenType type_;
        std::string lexeme_;
        Value value_;
        int line_;
    };

} // namespace yeep
