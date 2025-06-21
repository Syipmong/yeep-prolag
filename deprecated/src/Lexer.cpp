#include "core/Lexer.hpp"
#include <cctype>
#include <unordered_map>
#include <stdexcept>

namespace yeep {
    
    // Static keyword map for efficient lookup
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"let", TokenType::LET},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"else", TokenType::ELSE},
        {"while", TokenType::WHILE},
        {"true", TokenType::TRUE},
        {"false", TokenType::FALSE},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN}
    };
    
    Lexer::Lexer(const std::string& source)
        : source_(source), current_(0), line_(1), column_(1) {}
      std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;
        tokens.reserve(source_.length() / 4); // Rough estimate
        
        while (!isAtEnd()) {
            Token token = nextToken();
            tokens.push_back(token);
            
            if (token.getType() == TokenType::EOF_TOKEN) {
                break;
            }
        }
        
        // Ensure we always have an EOF token
        if (tokens.empty() || tokens.back().getType() != TokenType::EOF_TOKEN) {
            tokens.push_back(Token(TokenType::EOF_TOKEN, "", line_, column_));
        }
        
        return tokens;
    }
    
    Token Lexer::nextToken() {
        skipWhitespace();
        
        if (isAtEnd()) {
            return Token(TokenType::EOF_TOKEN, "", line_, column_);
        }
        
        int tokenLine = line_;
        int tokenColumn = column_;
        
        char c = advance();
        
        // Handle newlines properly (this fixes the newline handling issues)
        if (c == '\n') {
            return Token(TokenType::NEWLINE, "\\n", tokenLine, tokenColumn);
        }
        
        // Single-character tokens
        switch (c) {
            case '(': return Token(TokenType::LEFT_PAREN, "(", tokenLine, tokenColumn);
            case ')': return Token(TokenType::RIGHT_PAREN, ")", tokenLine, tokenColumn);
            case '{': return Token(TokenType::LEFT_BRACE, "{", tokenLine, tokenColumn);
            case '}': return Token(TokenType::RIGHT_BRACE, "}", tokenLine, tokenColumn);
            case ',': return Token(TokenType::COMMA, ",", tokenLine, tokenColumn);
            case ';': return Token(TokenType::SEMICOLON, ";", tokenLine, tokenColumn);
            case '+': return Token(TokenType::PLUS, "+", tokenLine, tokenColumn);
            case '-': return Token(TokenType::MINUS, "-", tokenLine, tokenColumn);
            case '*': return Token(TokenType::MULTIPLY, "*", tokenLine, tokenColumn);
            case '/':
                if (peek() == '/') {
                    // Skip single-line comment
                    while (peek() != '\n' && !isAtEnd()) {
                        advance();
                    }
                    return nextToken(); // Recursively get next token
                }
                return Token(TokenType::DIVIDE, "/", tokenLine, tokenColumn);
        }
        
        // Two-character tokens
        if (c == '=') {
            if (match('=')) {
                return Token(TokenType::EQUAL, "==", tokenLine, tokenColumn);
            }
            return Token(TokenType::ASSIGN, "=", tokenLine, tokenColumn);
        }
        
        if (c == '!') {
            if (match('=')) {
                return Token(TokenType::NOT_EQUAL, "!=", tokenLine, tokenColumn);
            }
            throw LexerError("Unexpected character '!'", line_, column_);
        }
        
        if (c == '<') {
            if (match('=')) {
                return Token(TokenType::LESS_EQUAL, "<=", tokenLine, tokenColumn);
            }
            return Token(TokenType::LESS, "<", tokenLine, tokenColumn);
        }
        
        if (c == '>') {
            if (match('=')) {
                return Token(TokenType::GREATER_EQUAL, ">=", tokenLine, tokenColumn);
            }
            return Token(TokenType::GREATER, ">", tokenLine, tokenColumn);
        }
        
        // String literals
        if (c == '"') {
            return scanString(tokenLine, tokenColumn);
        }
        
        // Numbers
        if (std::isdigit(c)) {
            return scanNumber(tokenLine, tokenColumn);
        }
        
        // Identifiers and keywords
        if (std::isalpha(c) || c == '_') {
            return scanIdentifier(tokenLine, tokenColumn);
        }
        
        // Unknown character
        std::string errorMsg = "Unexpected character: '";
        errorMsg += c;
        errorMsg += "'";
        throw LexerError(errorMsg, line_, column_);
    }
    
    bool Lexer::isAtEnd() const {
        return current_ >= source_.length();
    }
    
    char Lexer::advance() {
        if (isAtEnd()) return '\0';
        
        char c = source_[current_++];
        
        // Proper newline handling - this is a key improvement over the C version
        if (c == '\n') {
            line_++;
            column_ = 1;
        } else if (c == '\t') {
            column_ += 4; // Tab width of 4
        } else {
            column_++;
        }
        
        return c;
    }
    
    char Lexer::peek() const {
        if (isAtEnd()) return '\0';
        return source_[current_];
    }
    
    char Lexer::peekNext() const {
        if (current_ + 1 >= source_.length()) return '\0';
        return source_[current_ + 1];
    }
    
    bool Lexer::match(char expected) {
        if (isAtEnd()) return false;
        if (source_[current_] != expected) return false;
        
        advance();
        return true;
    }
    
    void Lexer::skipWhitespace() {
        while (!isAtEnd()) {
            char c = peek();
            
            // Skip spaces, tabs, carriage returns, form feeds, vertical tabs
            // But preserve newlines as they are significant tokens
            if (c == ' ' || c == '\t' || c == '\r' || c == '\f' || c == '\v') {
                advance();
            } else if (c > 0 && c < 32 && c != '\n') {
                // Skip other control characters but preserve newlines
                advance();
            } else {
                break;
            }
        }
    }
    
    Token Lexer::scanString(int line, int column) {
        std::string value;
        
        while (peek() != '"' && !isAtEnd()) {
            char c = peek();
            if (c == '\n') {
                line_++; // Track line numbers in multi-line strings
                column_ = 1;
            }
            
            // Handle escape sequences
            if (c == '\\') {
                advance(); // Skip the backslash
                char escaped = advance();
                switch (escaped) {
                    case 'n': value += '\n'; break;
                    case 't': value += '\t'; break;
                    case 'r': value += '\r'; break;
                    case '\\': value += '\\'; break;
                    case '"': value += '"'; break;
                    default:
                        value += escaped; // Unknown escape, just include as-is
                        break;
                }
            } else {
                value += advance();
            }
        }
        
        if (isAtEnd()) {
            throw LexerError("Unterminated string", line, column);
        }
        
        // Consume closing quote
        advance();
        
        return Token(TokenType::STRING, value, TokenValue(value), line, column);
    }
    
    Token Lexer::scanNumber(int line, int column) {
        std::string value;
        value += source_[current_ - 1]; // Include the first digit
        
        bool hasDot = false;
        
        while (!isAtEnd()) {
            char c = peek();
            
            if (std::isdigit(c)) {
                value += advance();
            } else if (c == '.' && !hasDot) {
                hasDot = true;
                value += advance();
            } else {
                break;
            }
        }
        
        // Convert to numeric value
        if (hasDot) {
            double doubleValue = std::stod(value);
            return Token(TokenType::NUMBER, value, TokenValue(doubleValue), line, column);
        } else {
            int intValue = std::stoi(value);
            return Token(TokenType::NUMBER, value, TokenValue(intValue), line, column);
        }
    }
    
    Token Lexer::scanIdentifier(int line, int column) {
        std::string value;
        value += source_[current_ - 1]; // Include the first character
        
        while (!isAtEnd()) {
            char c = peek();
            if (std::isalnum(c) || c == '_') {
                value += advance();
            } else {
                break;
            }
        }
        
        // Check if it's a keyword
        auto it = keywords.find(value);
        TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
        
        // For boolean keywords, include the value
        if (type == TokenType::TRUE) {
            return Token(type, value, TokenValue(true), line, column);
        } else if (type == TokenType::FALSE) {
            return Token(type, value, TokenValue(false), line, column);
        }
        
        return Token(type, value, line, column);
    }
    
} // namespace yeep
