#include "core/Parser.hpp"
#include "ast/Expression.hpp"
#include <iostream>

namespace yeep {
    
    Parser::Parser(const std::vector<Token>& tokens)
        : tokens_(tokens), current_(0), hadError_(false) {}
    
    std::vector<std::unique_ptr<Expression>> Parser::parse() {
        std::vector<std::unique_ptr<Expression>> statements;
        
        while (!isAtEnd()) {
            skipNewlines(); // Improved newline handling
            
            if (isAtEnd()) break;
            
            try {
                auto stmt = statement();
                if (stmt) {
                    statements.push_back(std::move(stmt));
                }
            } catch (const ParseError& error) {
                std::cerr << "Parse error: " << error.what() << std::endl;
                hadError_ = true;
                synchronize();
            }
        }
        
        return statements;
    }
    
    std::unique_ptr<Expression> Parser::parseExpression() {
        try {
            return assignment();
        } catch (const ParseError& error) {
            std::cerr << "Parse error: " << error.what() << std::endl;
            hadError_ = true;
            return nullptr;
        }
    }
    
    // Token management methods
    const Token& Parser::current() const {
        if (isAtEnd()) {
            static Token eofToken(TokenType::EOF_TOKEN, "", -1, -1);
            return eofToken;
        }
        return tokens_[current_];
    }
    
    const Token& Parser::previous() const {
        return tokens_[current_ - 1];
    }
    
    bool Parser::isAtEnd() const {
        return current_ >= tokens_.size() || current().getType() == TokenType::EOF_TOKEN;
    }
    
    Token Parser::advance() {
        if (!isAtEnd()) current_++;
        return previous();
    }
    
    bool Parser::check(TokenType type) const {
        if (isAtEnd()) return false;
        return current().getType() == type;
    }
    
    bool Parser::match(std::initializer_list<TokenType> types) {
        for (auto type : types) {
            if (check(type)) {
                advance();
                return true;
            }
        }
        return false;
    }
    
    Token Parser::consume(TokenType type, const std::string& message) {
        if (check(type)) return advance();
        
        throw ParseError(message, current());
    }
    
    // Improved newline handling - this is a key improvement over the C version
    void Parser::skipNewlines() {
        while (match({TokenType::NEWLINE})) {
            // Skip all consecutive newlines
        }
    }
    
    // Expression parsing methods (precedence climbing)
    std::unique_ptr<Expression> Parser::assignment() {
        auto expr = logicalOr();
        
        if (match({TokenType::ASSIGN})) {
            Token equals = previous();
            auto value = assignment();
            
            // Check if left side is a variable
            auto* varExpr = dynamic_cast<VariableExpression*>(expr.get());
            if (varExpr) {
                Token name = varExpr->getName();
                expr.release(); // Release ownership since we're not using it
                return std::make_unique<AssignmentExpression>(name, std::move(value));
            }
            
            throw ParseError("Invalid assignment target", equals);
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::logicalOr() {
        auto expr = logicalAnd();
        
        while (match({TokenType::OR})) {
            Token operator_ = previous();
            auto right = logicalAnd();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::logicalAnd() {
        auto expr = equality();
        
        while (match({TokenType::AND})) {
            Token operator_ = previous();
            auto right = equality();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::equality() {
        auto expr = comparison();
        
        while (match({TokenType::NOT_EQUAL, TokenType::EQUAL})) {
            Token operator_ = previous();
            auto right = comparison();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::comparison() {
        auto expr = term();
        
        while (match({TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL})) {
            Token operator_ = previous();
            auto right = term();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::term() {
        auto expr = factor();
        
        while (match({TokenType::MINUS, TokenType::PLUS})) {
            Token operator_ = previous();
            auto right = factor();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::factor() {
        auto expr = unary();
        
        while (match({TokenType::DIVIDE, TokenType::MULTIPLY})) {
            Token operator_ = previous();
            auto right = unary();
            expr = std::make_unique<BinaryExpression>(std::move(expr), operator_, std::move(right));
        }
        
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::unary() {
        if (match({TokenType::NOT, TokenType::MINUS})) {
            Token operator_ = previous();
            auto right = unary();
            return std::make_unique<UnaryExpression>(operator_, std::move(right));
        }
        
        return primary();
    }
    
    std::unique_ptr<Expression> Parser::primary() {
        if (match({TokenType::TRUE})) {
            return std::make_unique<LiteralExpression>(TokenValue(true));
        }
        
        if (match({TokenType::FALSE})) {
            return std::make_unique<LiteralExpression>(TokenValue(false));
        }
        
        if (match({TokenType::NUMBER})) {
            return std::make_unique<LiteralExpression>(previous().getValue());
        }
        
        if (match({TokenType::STRING})) {
            return std::make_unique<LiteralExpression>(previous().getValue());
        }
        
        if (match({TokenType::IDENTIFIER})) {
            return std::make_unique<VariableExpression>(previous());
        }
        
        if (match({TokenType::LEFT_PAREN})) {
            auto expr = parseExpression();
            consume(TokenType::RIGHT_PAREN, "Expected ')' after expression");
            return expr;
        }
        
        throw ParseError("Expected expression", current());
    }
    
    // Statement parsing methods
    std::unique_ptr<Expression> Parser::statement() {
        skipNewlines();
        
        if (match({TokenType::LET})) {
            return letStatement();
        }
        
        if (match({TokenType::PRINT})) {
            return printStatement();
        }
        
        if (match({TokenType::IF})) {
            return ifStatement();
        }
        
        if (match({TokenType::WHILE})) {
            return whileStatement();
        }
        
        if (match({TokenType::LEFT_BRACE})) {
            return block();
        }
        
        return expressionStatement();
    }
    
    std::unique_ptr<Expression> Parser::letStatement() {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name");
        
        std::unique_ptr<Expression> initializer = nullptr;
        if (match({TokenType::ASSIGN})) {
            initializer = parseExpression();
        }
        
        skipNewlines();
        return std::make_unique<LetStatement>(name, std::move(initializer));
    }
    
    std::unique_ptr<Expression> Parser::printStatement() {
        auto expr = parseExpression();
        skipNewlines();
        return std::make_unique<PrintStatement>(std::move(expr));
    }
    
    std::unique_ptr<Expression> Parser::expressionStatement() {
        auto expr = parseExpression();
        skipNewlines();
        return expr;
    }
    
    std::unique_ptr<Expression> Parser::block() {
        std::vector<std::unique_ptr<Expression>> statements;
        
        while (!check(TokenType::RIGHT_BRACE) && !isAtEnd()) {
            skipNewlines();
            if (check(TokenType::RIGHT_BRACE)) break;
            
            auto stmt = statement();
            if (stmt) {
                statements.push_back(std::move(stmt));
            }
        }
        
        consume(TokenType::RIGHT_BRACE, "Expected '}' after block");
        return std::make_unique<BlockStatement>(std::move(statements));
    }
    
    std::unique_ptr<Expression> Parser::ifStatement() {
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'if'");
        auto condition = parseExpression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after if condition");
        
        skipNewlines();
        auto thenBranch = statement();
        
        std::unique_ptr<Expression> elseBranch = nullptr;
        if (match({TokenType::ELSE})) {
            skipNewlines();
            elseBranch = statement();
        }
        
        return std::make_unique<IfStatement>(std::move(condition), std::move(thenBranch), std::move(elseBranch));
    }
    
    std::unique_ptr<Expression> Parser::whileStatement() {
        consume(TokenType::LEFT_PAREN, "Expected '(' after 'while'");
        auto condition = parseExpression();
        consume(TokenType::RIGHT_PAREN, "Expected ')' after while condition");
        
        skipNewlines();
        auto body = statement();
        
        return std::make_unique<WhileStatement>(std::move(condition), std::move(body));
    }
    
    std::unique_ptr<Expression> Parser::functionDeclaration() {
        // TODO: Implement function declarations in future
        throw ParseError("Function declarations not yet implemented", current());
    }
    
    // Error handling
    void Parser::error(const std::string& message) {
        throw ParseError(message, current());
    }
    
    void Parser::synchronize() {
        advance();
        
        while (!isAtEnd()) {
            if (previous().getType() == TokenType::NEWLINE) return;
            
            switch (current().getType()) {
                case TokenType::FUN:
                case TokenType::LET:
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
