#include "core/Token.hpp"
#include <stdexcept>
#include <unordered_map>

namespace yeep {
    
    Token::Token() 
        : type_(TokenType::INVALID), lexeme_(""), line_(1), column_(1) {}
    
    Token::Token(TokenType type, const std::string& lexeme, int line, int column)
        : type_(type), lexeme_(lexeme), line_(line), column_(column) {}
    
    Token::Token(TokenType type, const std::string& lexeme, const TokenValue& value, int line, int column)
        : type_(type), lexeme_(lexeme), value_(value), line_(line), column_(column) {}
    
    bool Token::isOneOf(std::initializer_list<TokenType> types) const {
        for (auto type : types) {
            if (type_ == type) return true;
        }
        return false;
    }
    
    std::string Token::toString() const {
        std::string result = typeToString(type_) + " '" + lexeme_ + "'";
        if (line_ > 1 || column_ > 1) {
            result += " at line " + std::to_string(line_) + ", column " + std::to_string(column_);
        }
        return result;
    }
      double Token::getNumber() const {
        if (value_.isNumber()) {
            return value_.getDouble();
        }
        throw std::runtime_error("Token is not a number");
    }
      std::string Token::getString() const {
        if (value_.isString()) {
            return value_.getString();
        }
        // If no value stored, return lexeme
        return lexeme_;
    }
      bool Token::getBoolean() const {
        if (value_.isBool()) {
            return value_.getBool();
        }
        throw std::runtime_error("Token is not a boolean");
    }
    
    std::string Token::typeToString(TokenType type) {
        static const std::unordered_map<TokenType, std::string> type_names = {
            {TokenType::NUMBER, "NUMBER"},
            {TokenType::STRING, "STRING"},
            {TokenType::BOOLEAN, "BOOLEAN"},
            {TokenType::IDENTIFIER, "IDENTIFIER"},
            {TokenType::PLUS, "PLUS"},
            {TokenType::MINUS, "MINUS"},
            {TokenType::MULTIPLY, "MULTIPLY"},
            {TokenType::DIVIDE, "DIVIDE"},
            {TokenType::MODULO, "MODULO"},
            {TokenType::ASSIGN, "ASSIGN"},
            {TokenType::EQUAL, "EQUAL"},
            {TokenType::NOT_EQUAL, "NOT_EQUAL"},
            {TokenType::LESS, "LESS"},
            {TokenType::LESS_EQUAL, "LESS_EQUAL"},
            {TokenType::GREATER, "GREATER"},
            {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
            {TokenType::AND, "AND"},
            {TokenType::OR, "OR"},
            {TokenType::NOT, "NOT"},
            {TokenType::LET, "LET"},
            {TokenType::FUN, "FUN"},
            {TokenType::PRINT, "PRINT"},
            {TokenType::IF, "IF"},
            {TokenType::ELSE, "ELSE"},
            {TokenType::WHILE, "WHILE"},
            {TokenType::FOR, "FOR"},
            {TokenType::FUNCTION, "FUNCTION"},
            {TokenType::RETURN, "RETURN"},
            {TokenType::TRUE, "TRUE"},
            {TokenType::FALSE, "FALSE"},
            {TokenType::SEMICOLON, "SEMICOLON"},
            {TokenType::COMMA, "COMMA"},
            {TokenType::LEFT_PAREN, "LEFT_PAREN"},
            {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
            {TokenType::LEFT_BRACE, "LEFT_BRACE"},
            {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
            {TokenType::LEFT_BRACKET, "LEFT_BRACKET"},
            {TokenType::RIGHT_BRACKET, "RIGHT_BRACKET"},
            {TokenType::NEWLINE, "NEWLINE"},
            {TokenType::EOF_TOKEN, "EOF"},
            {TokenType::INVALID, "INVALID"}
        };
        
        auto it = type_names.find(type);
        return (it != type_names.end()) ? it->second : "UNKNOWN";
    }
    
    bool Token::isKeyword(const std::string& lexeme) {
        static const std::unordered_map<std::string, TokenType> keywords = {
            {"let", TokenType::LET},
            {"fun", TokenType::FUN},
            {"print", TokenType::PRINT},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"for", TokenType::FOR},
            {"function", TokenType::FUNCTION},
            {"return", TokenType::RETURN},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"and", TokenType::AND},
            {"or", TokenType::OR},
            {"not", TokenType::NOT}
        };
        
        return keywords.find(lexeme) != keywords.end();
    }
    
    TokenType Token::getKeywordType(const std::string& lexeme) {
        static const std::unordered_map<std::string, TokenType> keywords = {
            {"let", TokenType::LET},
            {"fun", TokenType::FUN},
            {"print", TokenType::PRINT},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"for", TokenType::FOR},
            {"function", TokenType::FUNCTION},
            {"return", TokenType::RETURN},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"and", TokenType::AND},
            {"or", TokenType::OR},
            {"not", TokenType::NOT}
        };
        
        auto it = keywords.find(lexeme);
        return (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
    }
}
