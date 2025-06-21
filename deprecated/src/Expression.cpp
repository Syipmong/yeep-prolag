#include "ast/Expression.hpp"
#include "core/Interpreter.hpp"
#include <sstream>

namespace yeep {
    
    // LiteralExpression implementation
    TokenValue LiteralExpression::accept(Interpreter& interpreter) {
        return value_;
    }
    
    std::string LiteralExpression::toString() const {
        return value_.toString();
    }
    
    // VariableExpression implementation
    TokenValue VariableExpression::accept(Interpreter& interpreter) {
        return interpreter.evaluateVariable(name_);
    }
    
    std::string VariableExpression::toString() const {
        return name_.getLexeme();
    }
    
    // BinaryExpression implementation
    TokenValue BinaryExpression::accept(Interpreter& interpreter) {
        return interpreter.evaluateBinary(*this);
    }
    
    std::string BinaryExpression::toString() const {
        std::ostringstream oss;
        oss << "(" << left_->toString() << " " << operator_.getLexeme() << " " << right_->toString() << ")";
        return oss.str();
    }
    
    // UnaryExpression implementation
    TokenValue UnaryExpression::accept(Interpreter& interpreter) {
        return interpreter.evaluateUnary(*this);
    }
    
    std::string UnaryExpression::toString() const {
        std::ostringstream oss;
        oss << "(" << operator_.getLexeme() << right_->toString() << ")";
        return oss.str();
    }
    
    // AssignmentExpression implementation
    TokenValue AssignmentExpression::accept(Interpreter& interpreter) {
        return interpreter.evaluateAssignment(*this);
    }
    
    std::string AssignmentExpression::toString() const {
        std::ostringstream oss;
        oss << name_.getLexeme() << " = " << value_->toString();
        return oss.str();
    }
    
    // PrintStatement implementation
    TokenValue PrintStatement::accept(Interpreter& interpreter) {
        return interpreter.executePrint(*this);
    }
    
    std::string PrintStatement::toString() const {
        std::ostringstream oss;
        oss << "print " << expression_->toString();
        return oss.str();
    }
    
    // LetStatement implementation
    TokenValue LetStatement::accept(Interpreter& interpreter) {
        return interpreter.executeLet(*this);
    }
    
    std::string LetStatement::toString() const {
        std::ostringstream oss;
        oss << "let " << name_.getLexeme();
        if (initializer_) {
            oss << " = " << initializer_->toString();
        }
        return oss.str();
    }
    
    // BlockStatement implementation
    TokenValue BlockStatement::accept(Interpreter& interpreter) {
        return interpreter.executeBlock(*this);
    }
    
    std::string BlockStatement::toString() const {
        std::ostringstream oss;
        oss << "{ ";
        for (const auto& stmt : statements_) {
            oss << stmt->toString() << "; ";
        }
        oss << "}";
        return oss.str();
    }
    
    // IfStatement implementation
    TokenValue IfStatement::accept(Interpreter& interpreter) {
        return interpreter.executeIf(*this);
    }
    
    std::string IfStatement::toString() const {
        std::ostringstream oss;
        oss << "if (" << condition_->toString() << ") " << thenBranch_->toString();
        if (elseBranch_) {
            oss << " else " << elseBranch_->toString();
        }
        return oss.str();
    }
    
    // WhileStatement implementation
    TokenValue WhileStatement::accept(Interpreter& interpreter) {
        return interpreter.executeWhile(*this);
    }
    
    std::string WhileStatement::toString() const {
        std::ostringstream oss;
        oss << "while (" << condition_->toString() << ") " << body_->toString();
        return oss.str();
    }
    
    // CallExpression implementation
    TokenValue CallExpression::accept(Interpreter& interpreter) {
        return interpreter.evaluateCall(*this);
    }
    
    std::string CallExpression::toString() const {
        std::ostringstream oss;
        oss << name_.getLexeme() << "(";
        for (size_t i = 0; i < arguments_.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << arguments_[i]->toString();
        }
        oss << ")";
        return oss.str();
    }

} // namespace yeep
