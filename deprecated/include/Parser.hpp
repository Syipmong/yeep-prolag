#pragma once

#include "Token.hpp"
#include "ast/Expression.hpp"
#include <vector>
#include <memory>
#include <stdexcept>

namespace yeep {
    
    class ParseError : public std::runtime_error {
    public:
        ParseError(const std::string& message, const Token& token)
            : std::runtime_error(message), token_(token) {}
        
        const Token& getToken() const { return token_; }
        
    private:
        Token token_;
    };
    
    class Parser {
    public:
        explicit Parser(const std::vector<Token>& tokens);
        ~Parser() = default;
        
        // Main parsing methods
        std::vector<std::unique_ptr<Expression>> parse();
        std::unique_ptr<Expression> parseExpression();
        
        // Error recovery
        bool hadError() const { return hadError_; }
        void clearError() { hadError_ = false; }
        
    private:
        // Token management
        const Token& current() const;
        const Token& previous() const;
        bool isAtEnd() const;
        Token advance();
        bool check(TokenType type) const;
        bool match(std::initializer_list<TokenType> types);
        Token consume(TokenType type, const std::string& message);
        
        // Newline handling - improved from C version
        void skipNewlines();
        
        // Expression parsing (precedence climbing)
        std::unique_ptr<Expression> assignment();
        std::unique_ptr<Expression> logicalOr();
        std::unique_ptr<Expression> logicalAnd();
        std::unique_ptr<Expression> equality();
        std::unique_ptr<Expression> comparison();
        std::unique_ptr<Expression> term();
        std::unique_ptr<Expression> factor();
        std::unique_ptr<Expression> unary();
        std::unique_ptr<Expression> primary();
        
        // Statement parsing
        std::unique_ptr<Expression> statement();
        std::unique_ptr<Expression> letStatement();
        std::unique_ptr<Expression> printStatement();
        std::unique_ptr<Expression> expressionStatement();
        std::unique_ptr<Expression> block();
        std::unique_ptr<Expression> ifStatement();
        std::unique_ptr<Expression> whileStatement();
        std::unique_ptr<Expression> functionDeclaration();
        
        // Error handling
        void error(const std::string& message);
        void synchronize();
        
        // Member variables
        std::vector<Token> tokens_;
        size_t current_;
        bool hadError_;
    };
    
} // namespace yeep
