#include "Lexer.hpp"
#include <cctype>
#include <unordered_map>

namespace yeep {

    static std::unordered_map<std::string, TokenType> keywords = {
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"let", TokenType::LET},
        {"nil", TokenType::NIL},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"true", TokenType::TRUE},
        {"while", TokenType::WHILE}
    };

    Lexer::Lexer(const std::string& source) 
        : source_(source), current_(0), line_(1) {}

    std::vector<Token> Lexer::tokenize() {
        std::vector<Token> tokens;
        
        while (!isAtEnd()) {
            skipWhitespace();
            
            if (isAtEnd()) break;
            
            char c = advance();
            
            switch (c) {
                case '(': tokens.push_back(makeToken(TokenType::LEFT_PAREN)); break;
                case ')': tokens.push_back(makeToken(TokenType::RIGHT_PAREN)); break;
                case '{': tokens.push_back(makeToken(TokenType::LEFT_BRACE)); break;
                case '}': tokens.push_back(makeToken(TokenType::RIGHT_BRACE)); break;
                case ',': tokens.push_back(makeToken(TokenType::COMMA)); break;
                case ';': tokens.push_back(makeToken(TokenType::SEMICOLON)); break;
                case '+': tokens.push_back(makeToken(TokenType::PLUS)); break;
                case '-': tokens.push_back(makeToken(TokenType::MINUS)); break;
                case '*': tokens.push_back(makeToken(TokenType::MULTIPLY)); break;
                case '/': 
                    if (match('/')) {
                        skipComment();
                    } else {
                        tokens.push_back(makeToken(TokenType::DIVIDE));
                    }
                    break;
                case '%': tokens.push_back(makeToken(TokenType::MODULO)); break;
                case '!':
                    tokens.push_back(makeToken(match('=') ? TokenType::NOT_EQUAL : TokenType::NOT));
                    break;
                case '=':
                    tokens.push_back(makeToken(match('=') ? TokenType::EQUAL : TokenType::ASSIGN));
                    break;
                case '<':
                    tokens.push_back(makeToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS));
                    break;
                case '>':
                    tokens.push_back(makeToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER));
                    break;
                case '&':
                    if (match('&')) {
                        tokens.push_back(makeToken(TokenType::AND));
                    } else {
                        tokens.push_back(errorToken("Unexpected character '&'"));
                    }
                    break;
                case '|':
                    if (match('|')) {
                        tokens.push_back(makeToken(TokenType::OR));
                    } else {
                        tokens.push_back(errorToken("Unexpected character '|'"));
                    }
                    break;
                case '"': tokens.push_back(string()); break;
                default:
                    if (std::isdigit(c)) {
                        current_--; // Back up
                        tokens.push_back(number());
                    } else if (std::isalpha(c) || c == '_') {
                        current_--; // Back up
                        tokens.push_back(identifier());
                    } else {
                        tokens.push_back(errorToken("Unexpected character"));
                    }
                    break;
            }
        }
        
        tokens.push_back(makeToken(TokenType::EOF_TOKEN));
        return tokens;
    }

    bool Lexer::isAtEnd() const {
        return current_ >= source_.length();
    }

    char Lexer::advance() {
        return source_[current_++];
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
        current_++;
        return true;
    }

    void Lexer::skipWhitespace() {
        while (!isAtEnd()) {
            char c = peek();
            if (c == ' ' || c == '\r' || c == '\t') {
                advance();
            } else if (c == '\n') {
                line_++;
                advance();
            } else {
                break;
            }
        }
    }

    void Lexer::skipComment() {
        while (peek() != '\n' && !isAtEnd()) {
            advance();
        }
    }

    Token Lexer::makeToken(TokenType type) const {
        return Token(type, "", line_);
    }

    Token Lexer::makeToken(TokenType type, const Value& value) const {
        return Token(type, "", value, line_);
    }

    Token Lexer::errorToken(const std::string& message) const {
        return Token(TokenType::INVALID, message, line_);
    }

    Token Lexer::string() {
        std::string value;
        
        while (peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line_++;
            value += advance();
        }
        
        if (isAtEnd()) {
            return errorToken("Unterminated string");
        }
        
        advance(); // Closing quote
        return makeToken(TokenType::STRING, Value(value));
    }

    Token Lexer::number() {
        size_t start = current_;
        
        while (std::isdigit(peek())) {
            advance();
        }
        
        // Look for decimal part
        if (peek() == '.' && std::isdigit(peekNext())) {
            advance(); // Consume '.'
            while (std::isdigit(peek())) {
                advance();
            }
        }
        
        std::string numberStr = source_.substr(start, current_ - start);
        double value = std::stod(numberStr);
        return makeToken(TokenType::NUMBER, Value(value));
    }

    Token Lexer::identifier() {
        size_t start = current_;
        
        while (std::isalnum(peek()) || peek() == '_') {
            advance();
        }
        
        std::string text = source_.substr(start, current_ - start);
        
        // Check if it's a keyword
        auto it = keywords.find(text);
        TokenType type = (it != keywords.end()) ? it->second : TokenType::IDENTIFIER;
        
        if (type == TokenType::TRUE) {
            return makeToken(type, Value(true));
        } else if (type == TokenType::FALSE) {
            return makeToken(type, Value(false));
        } else if (type == TokenType::NIL) {
            return makeToken(type, Value());
        }
        
        return Token(type, text, line_);
    }

    TokenType Lexer::identifierType() const {
        return TokenType::IDENTIFIER; // Not used
    }

    TokenType Lexer::checkKeyword(size_t start, const std::string& rest, TokenType type) const {
        return TokenType::IDENTIFIER; // Not used
    }

} // namespace yeep
