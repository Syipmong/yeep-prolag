#include "core/Interpreter.hpp"
#include "core/BuiltinFunctions.hpp"
#include "ast/Expression.hpp"
#include <iostream>
#include <sstream>

namespace yeep {
    
    // Environment implementation
    Environment::Environment() : enclosing_(nullptr) {}
    
    Environment::Environment(std::shared_ptr<Environment> enclosing) 
        : enclosing_(enclosing) {}
    
    void Environment::define(const std::string& name, const TokenValue& value) {
        values_[name] = value;
    }
    
    TokenValue Environment::get(const Token& name) {
        auto it = values_.find(name.getLexeme());
        if (it != values_.end()) {
            return it->second;
        }
        
        if (enclosing_) {
            return enclosing_->get(name);
        }
        
        throw RuntimeError("Undefined variable '" + name.getLexeme() + "'", name);
    }
    
    void Environment::assign(const Token& name, const TokenValue& value) {
        auto it = values_.find(name.getLexeme());
        if (it != values_.end()) {
            it->second = value;
            return;
        }
        
        if (enclosing_) {
            enclosing_->assign(name, value);
            return;
        }
        
        throw RuntimeError("Undefined variable '" + name.getLexeme() + "'", name);
    }
      // Interpreter implementation
    Interpreter::Interpreter() : hadRuntimeError_(false) {
        globals_ = std::make_shared<Environment>();
        environment_ = globals_;
        
        // Initialize built-in functions
        BuiltinFunctions::initialize();
    }
    
    void Interpreter::interpret(const std::vector<std::unique_ptr<Expression>>& statements) {
        try {
            for (const auto& statement : statements) {
                evaluate(*statement);
            }
        } catch (const RuntimeError& error) {
            std::cerr << "Runtime error: " << error.what() << std::endl;
            std::cerr << "  at line " << error.getToken().getLine() 
                      << ", column " << error.getToken().getColumn() << std::endl;
            hadRuntimeError_ = true;
        }
    }
    
    TokenValue Interpreter::evaluate(Expression& expr) {
        return expr.accept(*this);
    }
    
    // Expression evaluation methods
    TokenValue Interpreter::evaluateVariable(const Token& name) {
        return environment_->get(name);
    }
    
    TokenValue Interpreter::evaluateBinary(const BinaryExpression& expr) {
        TokenValue left = evaluate(const_cast<Expression&>(expr.getLeft()));
        TokenValue right = evaluate(const_cast<Expression&>(expr.getRight()));
        
        switch (expr.getOperator().getType()) {
            case TokenType::PLUS:
                // Handle both numeric addition and string concatenation
                if (left.isNumber() && right.isNumber()) {
                    if (left.isInt() && right.isInt()) {
                        return TokenValue(left.getInt() + right.getInt());
                    } else {
                        return TokenValue(left.getDouble() + right.getDouble());
                    }
                } else if (left.isString() || right.isString()) {
                    return TokenValue(stringify(left) + stringify(right));
                }
                throw RuntimeError("Operands must be two numbers or at least one string", expr.getOperator());
                
            case TokenType::MINUS:
                if (left.isNumber() && right.isNumber()) {
                    if (left.isInt() && right.isInt()) {
                        return TokenValue(left.getInt() - right.getInt());
                    } else {
                        return TokenValue(left.getDouble() - right.getDouble());
                    }
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::MULTIPLY:
                if (left.isNumber() && right.isNumber()) {
                    if (left.isInt() && right.isInt()) {
                        return TokenValue(left.getInt() * right.getInt());
                    } else {
                        return TokenValue(left.getDouble() * right.getDouble());
                    }
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::DIVIDE:
                if (left.isNumber() && right.isNumber()) {
                    double divisor = right.getDouble();
                    if (divisor == 0.0) {
                        throw RuntimeError("Division by zero", expr.getOperator());
                    }
                    return TokenValue(left.getDouble() / divisor);
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::GREATER:
                if (left.isNumber() && right.isNumber()) {
                    return TokenValue(left.getDouble() > right.getDouble());
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::GREATER_EQUAL:
                if (left.isNumber() && right.isNumber()) {
                    return TokenValue(left.getDouble() >= right.getDouble());
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::LESS:
                if (left.isNumber() && right.isNumber()) {
                    return TokenValue(left.getDouble() < right.getDouble());
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::LESS_EQUAL:
                if (left.isNumber() && right.isNumber()) {
                    return TokenValue(left.getDouble() <= right.getDouble());
                }
                throw RuntimeError("Operands must be numbers", expr.getOperator());
                
            case TokenType::NOT_EQUAL:
                return TokenValue(!isEqual(left, right));
                
            case TokenType::EQUAL:
                return TokenValue(isEqual(left, right));
                
            default:
                throw RuntimeError("Unknown binary operator", expr.getOperator());
        }
    }
    
    TokenValue Interpreter::evaluateUnary(const UnaryExpression& expr) {
        TokenValue right = evaluate(const_cast<Expression&>(expr.getRight()));
        
        switch (expr.getOperator().getType()) {
            case TokenType::MINUS:
                if (right.isNumber()) {
                    if (right.isInt()) {
                        return TokenValue(-right.getInt());
                    } else {
                        return TokenValue(-right.getDouble());
                    }
                }
                throw RuntimeError("Operand must be a number", expr.getOperator());
                
            case TokenType::NOT:
                return TokenValue(!isTruthy(right));
                
            default:
                throw RuntimeError("Unknown unary operator", expr.getOperator());
        }
    }
    
    TokenValue Interpreter::evaluateAssignment(const AssignmentExpression& expr) {
        TokenValue value = evaluate(const_cast<Expression&>(expr.getValue()));
        environment_->assign(expr.getName(), value);
        return value;
    }
    
    TokenValue Interpreter::evaluateCall(const CallExpression& expr) {
        const std::string& functionName = expr.getName().getLexeme();
        
        // Check if it's a built-in function
        if (BuiltinFunctions::isBuiltin(functionName)) {
            // Evaluate all arguments
            std::vector<TokenValue> arguments;
            for (const auto& argExpr : expr.getArguments()) {
                arguments.push_back(evaluate(const_cast<Expression&>(*argExpr)));
            }
            
            // Call the built-in function
            try {
                BuiltinFunction func = BuiltinFunctions::getBuiltin(functionName);
                return func(arguments);
            } catch (const std::exception& e) {
                throw RuntimeError(e.what(), expr.getName());
            }
        }
        
        // TODO: Add support for user-defined functions in future version
        throw RuntimeError("Unknown function '" + functionName + "'", expr.getName());
    }

    // Statement execution methods
    TokenValue Interpreter::executePrint(const PrintStatement& stmt) {
        TokenValue value = evaluate(const_cast<Expression&>(stmt.getExpression()));
        std::cout << stringify(value) << std::endl;
        return TokenValue(); // Nil/void
    }
    
    TokenValue Interpreter::executeLet(const LetStatement& stmt) {
        TokenValue value;
        if (stmt.getInitializer()) {
            value = evaluate(const_cast<Expression&>(*stmt.getInitializer()));
        }
        
        environment_->define(stmt.getName().getLexeme(), value);
        return TokenValue(); // Nil/void
    }
    
    TokenValue Interpreter::executeBlock(const BlockStatement& stmt) {
        executeBlock(stmt.getStatements(), std::make_shared<Environment>(environment_));
        return TokenValue(); // Nil/void
    }
    
    void Interpreter::executeBlock(const std::vector<std::unique_ptr<Expression>>& statements,
                                  std::shared_ptr<Environment> environment) {
        auto previous = environment_;
        environment_ = environment;
        
        try {
            for (const auto& statement : statements) {
                evaluate(*statement);
            }
        } catch (...) {
            environment_ = previous;
            throw;
        }
        
        environment_ = previous;
    }
    
    TokenValue Interpreter::executeIf(const IfStatement& stmt) {
        TokenValue condition = evaluate(const_cast<Expression&>(stmt.getCondition()));
        
        if (isTruthy(condition)) {
            return evaluate(const_cast<Expression&>(stmt.getThenBranch()));
        } else if (stmt.getElseBranch()) {
            return evaluate(const_cast<Expression&>(*stmt.getElseBranch()));
        }
        
        return TokenValue(); // Nil/void
    }
    
    TokenValue Interpreter::executeWhile(const WhileStatement& stmt) {
        while (isTruthy(evaluate(const_cast<Expression&>(stmt.getCondition())))) {
            evaluate(const_cast<Expression&>(stmt.getBody()));
        }
        
        return TokenValue(); // Nil/void
    }
    
    // Utility methods
    bool Interpreter::isTruthy(const TokenValue& value) {
        if (value.isNil()) return false;
        if (value.isBool()) return value.getBool();
        return true; // Everything else is truthy
    }
    
    bool Interpreter::isEqual(const TokenValue& left, const TokenValue& right) {
        if (left.isNil() && right.isNil()) return true;
        if (left.isNil() || right.isNil()) return false;
        
        if (left.isBool() && right.isBool()) {
            return left.getBool() == right.getBool();
        }
        
        if (left.isNumber() && right.isNumber()) {
            return left.getDouble() == right.getDouble();
        }
        
        if (left.isString() && right.isString()) {
            return left.getString() == right.getString();
        }
        
        return false;
    }
    
    std::string Interpreter::stringify(const TokenValue& value) {
        if (value.isNil()) return "nil";
        if (value.isBool()) return value.getBool() ? "true" : "false";
        if (value.isString()) return value.getString();
        if (value.isNumber()) {
            if (value.isInt()) {
                return std::to_string(value.getInt());
            } else {
                std::ostringstream oss;
                oss << value.getDouble();
                std::string result = oss.str();
                // Remove trailing zeros for cleaner output
                if (result.find('.') != std::string::npos) {
                    result.erase(result.find_last_not_of('0') + 1, std::string::npos);
                    result.erase(result.find_last_not_of('.') + 1, std::string::npos);
                }
                return result;
            }
        }
        
        return "unknown";
    }
    
} // namespace yeep
