#pragma once

#include "core/Token.hpp"
#include <memory>
#include <vector>
#include <string>

namespace yeep {
    
    // Forward declarations
    class Interpreter;
    class Environment;
    
    // Base class for all AST nodes
    class Expression {
    public:
        virtual ~Expression() = default;
        
        // Pure virtual methods
        virtual TokenValue accept(Interpreter& interpreter) = 0;
        virtual std::string toString() const = 0;
        
        // Optional methods with default implementations
        virtual bool isStatement() const { return false; }
        virtual bool isLiteral() const { return false; }
    };
    
    // Literal expression (numbers, strings, booleans)
    class LiteralExpression : public Expression {
    public:
        explicit LiteralExpression(const TokenValue& value)
            : value_(value) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isLiteral() const override { return true; }
        
        const TokenValue& getValue() const { return value_; }
        
    private:
        TokenValue value_;
    };
    
    // Variable expression
    class VariableExpression : public Expression {
    public:
        explicit VariableExpression(const Token& name)
            : name_(name) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        
        const Token& getName() const { return name_; }
        
    private:
        Token name_;
    };
    
    // Binary expression (a + b, a == b, etc.)
    class BinaryExpression : public Expression {
    public:
        BinaryExpression(std::unique_ptr<Expression> left, const Token& operator_, std::unique_ptr<Expression> right)
            : left_(std::move(left)), operator_(operator_), right_(std::move(right)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        
        const Expression& getLeft() const { return *left_; }
        const Token& getOperator() const { return operator_; }
        const Expression& getRight() const { return *right_; }
        
    private:
        std::unique_ptr<Expression> left_;
        Token operator_;
        std::unique_ptr<Expression> right_;
    };
    
    // Unary expression (-a, !a)
    class UnaryExpression : public Expression {
    public:
        UnaryExpression(const Token& operator_, std::unique_ptr<Expression> right)
            : operator_(operator_), right_(std::move(right)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        
        const Token& getOperator() const { return operator_; }
        const Expression& getRight() const { return *right_; }
        
    private:
        Token operator_;
        std::unique_ptr<Expression> right_;
    };
    
    // Assignment expression (a = 5)
    class AssignmentExpression : public Expression {
    public:
        AssignmentExpression(const Token& name, std::unique_ptr<Expression> value)
            : name_(name), value_(std::move(value)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        
        const Token& getName() const { return name_; }
        const Expression& getValue() const { return *value_; }
        
    private:
        Token name_;
        std::unique_ptr<Expression> value_;
    };
    
    // Print statement
    class PrintStatement : public Expression {
    public:
        explicit PrintStatement(std::unique_ptr<Expression> expression)
            : expression_(std::move(expression)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isStatement() const override { return true; }
        
        const Expression& getExpression() const { return *expression_; }
        
    private:
        std::unique_ptr<Expression> expression_;
    };
    
    // Let statement (variable declaration)
    class LetStatement : public Expression {
    public:
        LetStatement(const Token& name, std::unique_ptr<Expression> initializer)
            : name_(name), initializer_(std::move(initializer)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isStatement() const override { return true; }
        
        const Token& getName() const { return name_; }
        const Expression* getInitializer() const { return initializer_.get(); }
        
    private:
        Token name_;
        std::unique_ptr<Expression> initializer_;
    };
    
    // Block statement
    class BlockStatement : public Expression {
    public:
        explicit BlockStatement(std::vector<std::unique_ptr<Expression>> statements)
            : statements_(std::move(statements)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isStatement() const override { return true; }
        
        const std::vector<std::unique_ptr<Expression>>& getStatements() const { return statements_; }
        
    private:
        std::vector<std::unique_ptr<Expression>> statements_;
    };
    
    // If statement
    class IfStatement : public Expression {
    public:
        IfStatement(std::unique_ptr<Expression> condition, 
                   std::unique_ptr<Expression> thenBranch,
                   std::unique_ptr<Expression> elseBranch = nullptr)
            : condition_(std::move(condition)), 
              thenBranch_(std::move(thenBranch)),
              elseBranch_(std::move(elseBranch)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isStatement() const override { return true; }
        
        const Expression& getCondition() const { return *condition_; }
        const Expression& getThenBranch() const { return *thenBranch_; }
        const Expression* getElseBranch() const { return elseBranch_.get(); }
        
    private:
        std::unique_ptr<Expression> condition_;
        std::unique_ptr<Expression> thenBranch_;
        std::unique_ptr<Expression> elseBranch_;
    };
    
    // While statement
    class WhileStatement : public Expression {
    public:
        WhileStatement(std::unique_ptr<Expression> condition, std::unique_ptr<Expression> body)
            : condition_(std::move(condition)), body_(std::move(body)) {}
        
        TokenValue accept(Interpreter& interpreter) override;
        std::string toString() const override;
        bool isStatement() const override { return true; }
        
        const Expression& getCondition() const { return *condition_; }
        const Expression& getBody() const { return *body_; }
        
    private:
        std::unique_ptr<Expression> condition_;
        std::unique_ptr<Expression> body_;
    };
    
} // namespace yeep
