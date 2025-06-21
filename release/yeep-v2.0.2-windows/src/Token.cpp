#include "Token.hpp"
#include <unordered_map>

namespace yeep {

    std::string Token::typeToString(TokenType type) {
        static std::unordered_map<TokenType, std::string> typeNames = {
            {TokenType::NUMBER, "NUMBER"},
            {TokenType::STRING, "STRING"},
            {TokenType::TRUE, "TRUE"},
            {TokenType::FALSE, "FALSE"},
            {TokenType::NIL, "NIL"},
            {TokenType::IDENTIFIER, "IDENTIFIER"},
            {TokenType::PLUS, "PLUS"},
            {TokenType::MINUS, "MINUS"},
            {TokenType::MULTIPLY, "MULTIPLY"},
            {TokenType::DIVIDE, "DIVIDE"},
            {TokenType::MODULO, "MODULO"},
            {TokenType::EQUAL, "EQUAL"},
            {TokenType::NOT_EQUAL, "NOT_EQUAL"},
            {TokenType::LESS, "LESS"},
            {TokenType::LESS_EQUAL, "LESS_EQUAL"},
            {TokenType::GREATER, "GREATER"},
            {TokenType::GREATER_EQUAL, "GREATER_EQUAL"},
            {TokenType::AND, "AND"},
            {TokenType::OR, "OR"},
            {TokenType::NOT, "NOT"},
            {TokenType::ASSIGN, "ASSIGN"},
            {TokenType::LEFT_PAREN, "LEFT_PAREN"},
            {TokenType::RIGHT_PAREN, "RIGHT_PAREN"},
            {TokenType::LEFT_BRACE, "LEFT_BRACE"},
            {TokenType::RIGHT_BRACE, "RIGHT_BRACE"},
            {TokenType::COMMA, "COMMA"},
            {TokenType::SEMICOLON, "SEMICOLON"},
            {TokenType::LET, "LET"},
            {TokenType::FUN, "FUN"},
            {TokenType::IF, "IF"},
            {TokenType::ELSE, "ELSE"},
            {TokenType::WHILE, "WHILE"},
            {TokenType::FOR, "FOR"},
            {TokenType::RETURN, "RETURN"},
            {TokenType::PRINT, "PRINT"},
            {TokenType::NEWLINE, "NEWLINE"},
            {TokenType::EOF_TOKEN, "EOF"},
            {TokenType::INVALID, "INVALID"}
        };
        
        auto it = typeNames.find(type);
        return it != typeNames.end() ? it->second : "UNKNOWN";
    }

} // namespace yeep
