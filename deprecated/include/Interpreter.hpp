#pragma once

#include "Token.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <stdexcept>

namespace yeep {
      // Forward declarations
    class Expression;
    class BinaryExpression;
    class UnaryExpression;
    class AssignmentExpression;
    class VariableExpression;
    class CallExpression;
    class PrintStatement;
    class LetStatement;
    class BlockStatement;
    class IfStatement;
    class WhileStatement;
    
    class RuntimeError : public std::runtime_error {
    public:
        RuntimeError(const std::string& message, const Token& token)
            : std::runtime_error(message), token_(token) {}
        
        const Token& getToken() const { return token_; }
        
    private:
        Token token_;
    };
    
    // Environment for variable storage with proper scoping
    class Environment {
    public:
        Environment();
        explicit Environment(std::shared_ptr<Environment> enclosing);
        
        void define(const std::string& name, const TokenValue& value);
        TokenValue get(const Token& name);
        void assign(const Token& name, const TokenValue& value);
        
    private:
        std::shared_ptr<Environment> enclosing_;
        std::unordered_map<std::string, TokenValue> values_;
    };
    
    class Interpreter {
    public:
        Interpreter();
        ~Interpreter() = default;
        
        // Main execution methods
        void interpret(const std::vector<std::unique_ptr<Expression>>& statements);
        TokenValue evaluate(Expression& expr);
        
        // Expression evaluation methods
        TokenValue evaluateVariable(const Token& name);
        TokenValue evaluateBinary(const BinaryExpression& expr);
        TokenValue evaluateUnary(const UnaryExpression& expr);
        TokenValue evaluateAssignment(const AssignmentExpression& expr);
        TokenValue evaluateCall(const CallExpression& expr);
        
        // Statement execution methods
        TokenValue executePrint(const PrintStatement& stmt);
        TokenValue executeLet(const LetStatement& stmt);
        TokenValue executeBlock(const BlockStatement& stmt);
        TokenValue executeIf(const IfStatement& stmt);
        TokenValue executeWhile(const WhileStatement& stmt);
          // Utility methods
        bool isTruthy(const TokenValue& value);
        bool isEqual(const TokenValue& left, const TokenValue& right);
        std::string stringify(const TokenValue& value);
        double getNumber(const TokenValue& value);
        
        // Error handling
        bool hadRuntimeError() const { return hadRuntimeError_; }
        void clearError() { hadRuntimeError_ = false; }
        
    private:
        // Environment management
        void executeBlock(const std::vector<std::unique_ptr<Expression>>& statements, 
                         std::shared_ptr<Environment> environment);
        
        // Member variables
        std::shared_ptr<Environment> globals_;
        std::shared_ptr<Environment> environment_;
        bool hadRuntimeError_;
    };
    
} // namespace yeep
