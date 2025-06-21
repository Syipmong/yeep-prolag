#pragma once

#include "Token.hpp"
#include "BuiltinFunctions.hpp"
#include <vector>
#include <unordered_map>
#include <memory>

namespace yeep {

    class Interpreter {
    public:
        Interpreter();
        void interpret(const std::vector<Token>& tokens);
        
    private:
        std::vector<Token> tokens_;
        size_t current_;
        std::unordered_map<std::string, Value> globals_;
        
        // Parser methods
        Value parseExpression();
        Value parseLogicalOr();
        Value parseLogicalAnd();
        Value parseEquality();
        Value parseComparison();
        Value parseTerm();
        Value parseFactor();
        Value parseUnary();
        Value parseCall();
        Value parsePrimary();
        
        // Statement parsing
        void parseStatement();
        void parsePrintStatement();
        void parseLetStatement();
        void parseExpressionStatement();
        void parseIfStatement();
        void parseWhileStatement();
        void parseBlockStatement();
        
        // Utility methods
        bool match(std::initializer_list<TokenType> types);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
        Token consume(TokenType type, const std::string& message);
        void skipStatement();
        
        // Expression evaluation
        Value evaluateBinary(const Value& left, TokenType op, const Value& right);
        Value evaluateUnary(TokenType op, const Value& operand);
        
        // Error handling
        void error(const std::string& message);
        void synchronize();
    };

} // namespace yeep
