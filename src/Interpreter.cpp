#include "Interpreter.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace yeep {

    Interpreter::Interpreter() : current_(0) {
        BuiltinFunctions::initialize();
    }

    void Interpreter::interpret(const std::vector<Token>& tokens) {
        tokens_ = tokens;
        current_ = 0;
        
        try {
            while (!isAtEnd()) {
                parseStatement();
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    // Statement parsing
    void Interpreter::parseStatement() {
        try {
            if (match({TokenType::PRINT})) {
                parsePrintStatement();
            } else if (match({TokenType::LET})) {
                parseLetStatement();
            } else {
                parseExpressionStatement();
            }
        } catch (const std::exception& e) {
            std::cerr << "Parse error: " << e.what() << std::endl;
            synchronize();
        }
    }

    void Interpreter::parsePrintStatement() {
        Value value = parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' after print statement");
        std::cout << value.toString() << std::endl;
    }

    void Interpreter::parseLetStatement() {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
        
        Value value;
        if (match({TokenType::ASSIGN})) {
            value = parseExpression();
        } // Otherwise, value remains nil
        
        consume(TokenType::SEMICOLON, "Expected ';' after variable declaration");
        globals_[name.getLexeme()] = value;
    }

    void Interpreter::parseExpressionStatement() {
        parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' after expression");
    }

    // Expression parsing (recursive descent)
    Value Interpreter::parseExpression() {
        return parseLogicalOr();
    }

    Value Interpreter::parseLogicalOr() {
        Value expr = parseLogicalAnd();
        
        while (match({TokenType::OR})) {
            TokenType op = previous().getType();
            Value right = parseLogicalAnd();
            
            // Short-circuit evaluation
            if (expr.isTruthy()) {
                return expr;
            }
            expr = right;
        }
        
        return expr;
    }

    Value Interpreter::parseLogicalAnd() {
        Value expr = parseEquality();
        
        while (match({TokenType::AND})) {
            TokenType op = previous().getType();
            Value right = parseEquality();
            
            // Short-circuit evaluation
            if (!expr.isTruthy()) {
                return expr;
            }
            expr = right;
        }
        
        return expr;
    }

    Value Interpreter::parseEquality() {
        Value expr = parseComparison();
        
        while (match({TokenType::NOT_EQUAL, TokenType::EQUAL})) {
            TokenType op = previous().getType();
            Value right = parseComparison();
            expr = evaluateBinary(expr, op, right);
        }
        
        return expr;
    }

    Value Interpreter::parseComparison() {
        Value expr = parseTerm();
        
        while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
            TokenType op = previous().getType();
            Value right = parseTerm();
            expr = evaluateBinary(expr, op, right);
        }
        
        return expr;
    }

    Value Interpreter::parseTerm() {
        Value expr = parseFactor();
        
        while (match({TokenType::MINUS, TokenType::PLUS})) {
            TokenType op = previous().getType();
            Value right = parseFactor();
            expr = evaluateBinary(expr, op, right);
        }
        
        return expr;
    }

    Value Interpreter::parseFactor() {
        Value expr = parseUnary();
        
        while (match({TokenType::DIVIDE, TokenType::MULTIPLY, TokenType::MODULO})) {
            TokenType op = previous().getType();
            Value right = parseUnary();
            expr = evaluateBinary(expr, op, right);
        }
        
        return expr;
    }

    Value Interpreter::parseUnary() {
        if (match({TokenType::NOT, TokenType::MINUS})) {
            TokenType op = previous().getType();
            Value right = parseUnary();
            return evaluateUnary(op, right);
        }
        
        return parseCall();
    }

    Value Interpreter::parseCall() {
        Value expr = parsePrimary();
        
        while (true) {
            if (match({TokenType::LEFT_PAREN})) {
                // This should be a function call
                if (!previous().getLexeme().empty()) {
                    // We need the function name from the primary expression
                    // For now, let's handle built-in functions in parsePrimary
                }
                break;
            } else {
                break;
            }
        }
        
        return expr;
    }

    Value Interpreter::parsePrimary() {
        if (match({TokenType::TRUE})) return previous().getValue();
        if (match({TokenType::FALSE})) return previous().getValue();
        if (match({TokenType::NIL})) return previous().getValue();
        
        if (match({TokenType::NUMBER, TokenType::STRING})) {
            return previous().getValue();
        }
        
        if (match({TokenType::IDENTIFIER})) {
            std::string name = previous().getLexeme();
            
            // Check for function call
            if (check(TokenType::LEFT_PAREN)) {
                advance(); // consume '('
                
                std::vector<Value> arguments;
                if (!check(TokenType::RIGHT_PAREN)) {
                    do {
                        arguments.push_back(parseExpression());
                    } while (match({TokenType::COMMA}));
                }
                
                consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments");
                
                // Check if it's a built-in function
                if (BuiltinFunctions::isBuiltin(name)) {
                    return BuiltinFunctions::call(name, arguments);
                } else {
                    throw std::runtime_error("Unknown function: " + name);
                }
            } else {
                // Variable access
                auto it = globals_.find(name);
                if (it != globals_.end()) {
                    return it->second;
                } else {
                    throw std::runtime_error("Undefined variable: " + name);
                }
            }
        }
        
        if (match({TokenType::LEFT_PAREN})) {
            Value expr = parseExpression();
            consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
            return expr;
        }
        
        throw std::runtime_error("Expected expression");
    }

    // Binary operations
    Value Interpreter::evaluateBinary(const Value& left, TokenType op, const Value& right) {
        switch (op) {
            case TokenType::PLUS:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() + right.getNumber());
                }
                if (left.isString() || right.isString()) {
                    return Value(left.toString() + right.toString());
                }
                throw std::runtime_error("Invalid operands for '+'");
                
            case TokenType::MINUS:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() - right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '-'");
                
            case TokenType::MULTIPLY:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() * right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '*'");
                
            case TokenType::DIVIDE:
                if (left.isNumber() && right.isNumber()) {
                    if (right.getNumber() == 0) {
                        throw std::runtime_error("Division by zero");
                    }
                    return Value(left.getNumber() / right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '/'");
                
            case TokenType::MODULO:
                if (left.isNumber() && right.isNumber()) {
                    return Value(fmod(left.getNumber(), right.getNumber()));
                }
                throw std::runtime_error("Invalid operands for '%'");
                
            case TokenType::GREATER:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() > right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '>'");
                
            case TokenType::GREATER_EQUAL:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() >= right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '>='");
                
            case TokenType::LESS:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() < right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '<'");
                
            case TokenType::LESS_EQUAL:
                if (left.isNumber() && right.isNumber()) {
                    return Value(left.getNumber() <= right.getNumber());
                }
                throw std::runtime_error("Invalid operands for '<='");
                
            case TokenType::EQUAL:
                // Handle equality for different types
                if (left.isNil() && right.isNil()) return Value(true);
                if (left.isNil() || right.isNil()) return Value(false);
                if (left.isBool() && right.isBool()) return Value(left.getBool() == right.getBool());
                if (left.isNumber() && right.isNumber()) return Value(left.getNumber() == right.getNumber());
                if (left.isString() && right.isString()) return Value(left.getString() == right.getString());
                return Value(false);
                  case TokenType::NOT_EQUAL: {
                Value eq = evaluateBinary(left, TokenType::EQUAL, right);
                return Value(!eq.getBool());
            }
                
            default:
                throw std::runtime_error("Unknown binary operator");
        }
    }

    Value Interpreter::evaluateUnary(TokenType op, const Value& operand) {
        switch (op) {
            case TokenType::MINUS:
                if (operand.isNumber()) {
                    return Value(-operand.getNumber());
                }
                throw std::runtime_error("Invalid operand for unary '-'");
                
            case TokenType::NOT:
                return Value(!operand.isTruthy());
                
            default:
                throw std::runtime_error("Unknown unary operator");
        }
    }

    // Utility methods
    bool Interpreter::match(std::initializer_list<TokenType> types) {
        for (TokenType type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }

    bool Interpreter::check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().getType() == type;
    }

    Token Interpreter::advance() {
        if (!isAtEnd()) current_++;
        return previous();
    }

    bool Interpreter::isAtEnd() {
        return peek().getType() == TokenType::EOF_TOKEN;
    }

    Token Interpreter::peek() {
        return tokens_[current_];
    }

    Token Interpreter::previous() {
        return tokens_[current_ - 1];
    }

    Token Interpreter::consume(TokenType type, const std::string& message) {
        if (check(type)) return advance();
        
        Token current = peek();
        throw std::runtime_error(message + " at line " + std::to_string(current.getLine()));
    }

    void Interpreter::error(const std::string& message) {
        Token current = peek();
        throw std::runtime_error(message + " at line " + std::to_string(current.getLine()));
    }

    void Interpreter::synchronize() {
        advance();
        
        while (!isAtEnd()) {
            if (previous().getType() == TokenType::SEMICOLON) return;
            
            switch (peek().getType()) {
                case TokenType::FUN:
                case TokenType::LET:
                case TokenType::FOR:
                case TokenType::IF:
                case TokenType::WHILE:
                case TokenType::PRINT:
                case TokenType::RETURN:
                    return;
                default:
                    break;
            }
            
            advance();
        }
    }

} // namespace yeep
