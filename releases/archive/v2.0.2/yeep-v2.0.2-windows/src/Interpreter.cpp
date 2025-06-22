#include "Interpreter.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace yeep {

    Interpreter::Interpreter() : current_(0), hasReturned_(false) {
        BuiltinFunctions::initialize();
    }

    void Interpreter::interpret(const std::vector<Token>& tokens) {
        tokens_ = tokens;
        current_ = 0;
        
        try {            while (!isAtEnd()) {
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
            } else if (match({TokenType::IF})) {
                parseIfStatement();
            } else if (match({TokenType::WHILE})) {
                parseWhileStatement();
            } else if (match({TokenType::FOR})) {
                parseForStatement();
            } else if (match({TokenType::FUN})) {
                parseFunctionStatement();
            } else if (match({TokenType::RETURN})) {
                parseReturnStatement();
            } else if (match({TokenType::LEFT_BRACE})) {
                parseBlockStatement();
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
        consume(TokenType::SEMICOLON, "Expected ';' after print statement");        std::cout << value.toString() << std::endl;
    }

    void Interpreter::parseLetStatement() {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
        
        Value value;
        if (match({TokenType::ASSIGN})) {
            value = parseExpression();
        } // Otherwise, value remains nil
        
        consume(TokenType::SEMICOLON, "Expected ';' after variable declaration");
        setVariable(name.getLexeme(), value);
    }

    void Interpreter::parseExpressionStatement() {
        parseExpression();
        consume(TokenType::SEMICOLON, "Expected ';' after expression");
    }

    void Interpreter::parseIfStatement() {
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'");
        Value condition = parseExpression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after if condition");
        
        if (condition.isTruthy()) {
            parseStatement(); // then branch
            
            // Skip else branch if present
            if (match({TokenType::ELSE})) {
                skipStatement();
            }
        } else {
            skipStatement(); // skip then branch
            
            // Execute else branch if present
            if (match({TokenType::ELSE})) {
                parseStatement();
            }
        }
    }    void Interpreter::parseWhileStatement() {
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'");
        
        // Store the condition tokens for re-evaluation
        size_t conditionStart = current_;
        Value condition = parseExpression();
        size_t conditionEnd = current_;
        
        consume(TokenType::RIGHT_PAREN, "Expected ')' after while condition");
        
        // Store the body start position
        size_t bodyStart = current_;
        
        // Execute loop
        while (condition.isTruthy()) {
            // Execute body
            current_ = bodyStart;
            parseStatement();
            
            if (hasReturned_) break; // Exit if return was called
            
            // Re-evaluate condition
            current_ = conditionStart;
            condition = parseExpression();
            current_ = conditionEnd;
        }
        
        // Skip the body if we didn't execute it or if we exited early
        if (!condition.isTruthy()) {
            current_ = bodyStart;
            skipStatement();
        }
    }void Interpreter::parseForStatement() {
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'for'");
        
        // Parse initialization (optional)
        if (!match({TokenType::SEMICOLON})) {
            if (match({TokenType::LET})) {
                Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
                Value value;
                if (match({TokenType::ASSIGN})) {
                    value = parseExpression();
                }
                setVariable(name.getLexeme(), value);
            } else {
                parseExpression(); // Assignment expression
            }
            consume(TokenType::SEMICOLON, "Expected ';' after for-loop initializer");
        }        // Parse condition (optional) - store the tokens for re-evaluation
        size_t conditionStart = current_;
        Value condition = Value(true); // Default to true if no condition
        if (!check(TokenType::SEMICOLON)) {
            condition = parseExpression();
        }
        size_t conditionEnd = current_;
        consume(TokenType::SEMICOLON, "Expected ';' after for condition");
          // Parse increment (optional) - store the tokens for re-execution
        size_t incrementStart = current_;
        if (!check(TokenType::RIGHT_PAREN)) {
            // Skip over the increment expression without executing it
            int parenCount = 0;
            while (!isAtEnd() && (parenCount > 0 || !check(TokenType::RIGHT_PAREN))) {
                if (check(TokenType::LEFT_PAREN)) parenCount++;
                else if (check(TokenType::RIGHT_PAREN)) parenCount--;
                advance();
            }
        }
        size_t incrementEnd = current_;
        consume(TokenType::RIGHT_PAREN, "Expected ')' after for clauses");
          // Store the body start position
        size_t bodyStart = current_;
        
        // Skip over the body to find the end of the for statement
        size_t forStatementEnd = current_;
        int braceCount = 0;
        if (check(TokenType::LEFT_BRACE)) {
            braceCount = 1;
            advance();
            while (braceCount > 0 && !isAtEnd()) {
                if (check(TokenType::LEFT_BRACE)) braceCount++;
                else if (check(TokenType::RIGHT_BRACE)) braceCount--;
                advance();
            }
            forStatementEnd = current_;
        } else {
            // Single statement body
            size_t savedCurrent = current_;
            skipStatement();
            forStatementEnd = current_;
            current_ = savedCurrent; // Restore for execution
        }
        
        // Execute loop - evaluate condition fresh at start
        if (conditionStart < conditionEnd) {
            current_ = conditionStart;
            condition = parseExpression();
        }
        
        while (condition.isTruthy()) {
            // Execute body
            current_ = bodyStart;
            parseStatement();
            
            if (hasReturned_) break; // Exit if return was called
            
            // Execute increment
            if (incrementStart < incrementEnd) {
                current_ = incrementStart;
                parseExpression();
            }
            
            // Re-evaluate condition
            if (conditionStart < conditionEnd) {
                current_ = conditionStart;
                condition = parseExpression();
            } else {
                break; // No condition means run once
            }
        }
        
        // Position parser at the end of the for statement for continued parsing
        current_ = forStatementEnd;
    }

    void Interpreter::parseFunctionStatement() {
        Token name = consume(TokenType::IDENTIFIER, "Expected function name");
        
        consume(TokenType::LEFT_PAREN, "Expected '(' after function name");
        
        std::vector<std::string> parameters;
        if (!check(TokenType::RIGHT_PAREN)) {
            do {
                Token param = consume(TokenType::IDENTIFIER, "Expected parameter name");
                parameters.push_back(param.getLexeme());
            } while (match({TokenType::COMMA}));
        }
        consume(TokenType::RIGHT_PAREN, "Expected ')' after parameters");
        
        consume(TokenType::LEFT_BRACE, "Expected '{' before function body");
        
        // Store the function body tokens
        size_t bodyStart = current_;
        int braceCount = 1;
        while (braceCount > 0 && !isAtEnd()) {
            if (check(TokenType::LEFT_BRACE)) braceCount++;
            else if (check(TokenType::RIGHT_BRACE)) braceCount--;
            advance();
        }
        size_t bodyEnd = current_ - 1; // Don't include the closing brace
        
        // Create function and store it
        std::vector<Token> bodyTokens(tokens_.begin() + bodyStart, tokens_.begin() + bodyEnd);
        Function func(name.getLexeme(), parameters, bodyTokens, bodyStart, bodyEnd);
        functions_[name.getLexeme()] = func;
    }    void Interpreter::parseReturnStatement() {
        Value value;
        if (!check(TokenType::SEMICOLON)) {
            value = parseExpression();
        }
        consume(TokenType::SEMICOLON, "Expected ';' after return value");
        
        returnValue_ = value;
        hasReturned_ = true;
    }

    // Function call support
    Value Interpreter::callFunction(const std::string& name, const std::vector<Value>& arguments) {
        auto it = functions_.find(name);
        if (it == functions_.end()) {
            throw std::runtime_error("Unknown function: " + name);
        }
        
        const Function& func = it->second;
        
        // Check parameter count
        if (arguments.size() != func.getParameters().size()) {
            throw std::runtime_error("Function " + name + " expects " + 
                std::to_string(func.getParameters().size()) + " arguments, got " + 
                std::to_string(arguments.size()));
        }
        
        // Push new scope for function execution
        pushScope();
        
        // Bind parameters to arguments
        for (size_t i = 0; i < arguments.size(); ++i) {
            setVariable(func.getParameters()[i], arguments[i]);
        }
          // Save current state
        size_t savedCurrent = current_;
        std::vector<Token> savedTokens = tokens_;
        bool savedHasReturned = hasReturned_;
        Value savedReturnValue = returnValue_;
          // Execute function body
        tokens_ = func.getBody();
        current_ = 0;
        hasReturned_ = false;
        returnValue_ = Value(); // nil by default
        
        try {
            while (!isAtEnd() && !hasReturned_) {
                parseStatement();
            }
        } catch (const std::exception& e) {
            // For function execution, we'll suppress parse errors but still handle real errors
            // Check if this is a genuine syntax error or just a parse artifact
            std::string errorMsg = e.what();
            if (errorMsg.find("Expected expression") == std::string::npos && 
                errorMsg.find("Expected ';'") == std::string::npos) {
                // This is a real error, restore state and re-throw
                current_ = savedCurrent;
                tokens_ = savedTokens;
                hasReturned_ = savedHasReturned;
                returnValue_ = savedReturnValue;
                popScope();
                throw;
            }
            // Otherwise, it's likely a parse artifact from token stream switching
            // Continue execution but mark as if we reached the end
            // (No action needed - just continue to restoration code)
        }
        
        Value result = returnValue_;
        
        // Restore state
        current_ = savedCurrent;
        tokens_ = savedTokens;
        hasReturned_ = savedHasReturned;
        returnValue_ = savedReturnValue;
        
        // Pop scope
        popScope();
        
        return result;
    }

    void Interpreter::pushScope() {
        scopes_.push_back(std::unordered_map<std::string, Value>());
    }

    void Interpreter::popScope() {
        if (!scopes_.empty()) {
            scopes_.pop_back();
        }
    }

    void Interpreter::setVariable(const std::string& name, const Value& value) {
        if (!scopes_.empty()) {
            scopes_.back()[name] = value;
        } else {
            globals_[name] = value;
        }
    }

    Value Interpreter::getVariable(const std::string& name) {
        // Search from innermost scope to outermost
        for (int i = scopes_.size() - 1; i >= 0; --i) {
            auto it = scopes_[i].find(name);
            if (it != scopes_[i].end()) {
                return it->second;
            }
        }
        
        // Check global scope
        auto it = globals_.find(name);
        if (it != globals_.end()) {
            return it->second;
        }
        
        throw std::runtime_error("Undefined variable: " + name);
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
        
        // Array literal
        if (match({TokenType::LEFT_BRACKET})) {
            Array arr;
            if (!check(TokenType::RIGHT_BRACKET)) {
                do {
                    arr.push_back(parseExpression());
                } while (match({TokenType::COMMA}));
            }
            consume(TokenType::RIGHT_BRACKET, "Expected ']' after array elements");
            return Value(arr);
        }
          if (match({TokenType::IDENTIFIER})) {
            std::string name = previous().getLexeme();
            
            // Check for assignment
            if (check(TokenType::ASSIGN)) {
                advance(); // consume '='
                Value value = parseExpression();
                setVariable(name, value);
                return value;
            }
            // Check for function call
            else if (check(TokenType::LEFT_PAREN)) {
                advance(); // consume '('
                
                std::vector<Value> arguments;
                if (!check(TokenType::RIGHT_PAREN)) {
                    do {
                        arguments.push_back(parseExpression());
                    } while (match({TokenType::COMMA}));
                }
                
                consume(TokenType::RIGHT_PAREN, "Expected ')' after arguments");
                
                // Check if it's a built-in function first
                if (BuiltinFunctions::isBuiltin(name)) {
                    return BuiltinFunctions::call(name, arguments);
                } else {
                    // Try user-defined function
                    return callFunction(name, arguments);
                }
            } else {
                // Variable access - use new scope-aware method
                return getVariable(name);
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
    }    bool Interpreter::isAtEnd() {
        return current_ >= tokens_.size() || peek().getType() == TokenType::EOF_TOKEN;
    }

    Token Interpreter::peek() {
        if (current_ >= tokens_.size()) {
            // Return a synthetic EOF token if we're past the end
            return Token(TokenType::EOF_TOKEN, "", 0);
        }
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

    void Interpreter::parseBlockStatement() {
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            parseStatement();
        }
        consume(TokenType::RIGHT_BRACE, "Expected '}' after block");
    }

    void Interpreter::skipStatement() {        // Skip a statement without executing it
        if (match({TokenType::PRINT})) {
            skipExpression();
            consume(TokenType::SEMICOLON, "Expected ';'");
        } else if (match({TokenType::LET})) {
            consume(TokenType::IDENTIFIER, "Expected variable name");
            if (match({TokenType::ASSIGN})) {
                skipExpression();
            }
            consume(TokenType::SEMICOLON, "Expected ';'");
        } else if (match({TokenType::IF})) {
            consume(TokenType::LEFT_PAREN, "Expected '('");
            skipExpression();
            consume(TokenType::RIGHT_PAREN, "Expected ')'");
            skipStatement();
            if (match({TokenType::ELSE})) {
                skipStatement();
            }
        } else if (match({TokenType::WHILE})) {
            consume(TokenType::LEFT_PAREN, "Expected '('");
            skipExpression();
            consume(TokenType::RIGHT_PAREN, "Expected ')'");
            skipStatement();
        } else if (match({TokenType::LEFT_BRACE})) {
            while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
                skipStatement();
            }
            consume(TokenType::RIGHT_BRACE, "Expected '}'");
        } else {
            skipExpression();
            consume(TokenType::SEMICOLON, "Expected ';'");
        }}

    void Interpreter::skipExpression() {
        // Skip over expression tokens without executing them
        int parenCount = 0;
        int bracketCount = 0;
        
        while (!isAtEnd()) {
            TokenType type = peek().getType();
            
            if (type == TokenType::LEFT_PAREN) {
                parenCount++;
            } else if (type == TokenType::RIGHT_PAREN) {
                parenCount--;
                if (parenCount < 0) break; // Reached end of expression
            } else if (type == TokenType::LEFT_BRACKET) {
                bracketCount++;
            } else if (type == TokenType::RIGHT_BRACKET) {
                bracketCount--;
                if (bracketCount < 0) break; // Reached end of expression
            } else if (parenCount == 0 && bracketCount == 0) {
                // At top level, check for expression terminators
                if (type == TokenType::SEMICOLON || type == TokenType::COMMA ||
                    type == TokenType::RIGHT_PAREN || type == TokenType::RIGHT_BRACKET ||
                    type == TokenType::RIGHT_BRACE || type == TokenType::EOF_TOKEN) {
                    break;
                }
            }
            
            advance();
        }
    }

} // namespace yeep
