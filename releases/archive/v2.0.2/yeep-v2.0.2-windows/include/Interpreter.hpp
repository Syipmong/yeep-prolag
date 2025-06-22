#pragma once

#include "Token.hpp"
#include "BuiltinFunctions.hpp"
#include <vector>
#include <unordered_map>
#include <memory>

namespace yeep {

    // Forward declarations
    class Interpreter;    // User-defined function class
    class Function {
    public:
        Function() = default; // Default constructor for std::unordered_map
        Function(const std::string& name, const std::vector<std::string>& params, 
                 const std::vector<Token>& body, size_t bodyStart, size_t bodyEnd)
            : name_(name), parameters_(params), body_(body), bodyStart_(bodyStart), bodyEnd_(bodyEnd) {}
        
        const std::string& getName() const { return name_; }
        const std::vector<std::string>& getParameters() const { return parameters_; }
        const std::vector<Token>& getBody() const { return body_; }
        size_t getBodyStart() const { return bodyStart_; }
        size_t getBodyEnd() const { return bodyEnd_; }
        
    private:
        std::string name_;
        std::vector<std::string> parameters_;
        std::vector<Token> body_;
        size_t bodyStart_;
        size_t bodyEnd_;
    };

    class Interpreter {
    public:
        Interpreter();
        void interpret(const std::vector<Token>& tokens);
        
    private:        std::vector<Token> tokens_;
        size_t current_;
        std::unordered_map<std::string, Value> globals_;
        std::unordered_map<std::string, Function> functions_;
        std::vector<std::unordered_map<std::string, Value>> scopes_; // For function local variables
        Value returnValue_; // For function returns
        bool hasReturned_; // Flag to indicate return
        
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
        void parseForStatement();
        void parseBlockStatement();
        void parseFunctionStatement();
        void parseReturnStatement();
          // Utility methods
        bool match(std::initializer_list<TokenType> types);
        bool check(TokenType type);
        Token advance();
        bool isAtEnd();
        Token peek();
        Token previous();
        Token consume(TokenType type, const std::string& message);
        void skipStatement();
        void skipExpression(); // Skip over expression tokens without executing
        
        // Function call support
        Value callFunction(const std::string& name, const std::vector<Value>& arguments);
        void pushScope();
        void popScope();
        void setVariable(const std::string& name, const Value& value);
        Value getVariable(const std::string& name);
        
        // Expression evaluation
        Value evaluateBinary(const Value& left, TokenType op, const Value& right);
        Value evaluateUnary(TokenType op, const Value& operand);
        
        // Error handling
        void error(const std::string& message);
        void synchronize();
    };

} // namespace yeep
