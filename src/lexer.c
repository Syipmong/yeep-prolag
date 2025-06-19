#include "yeep.h"

static bool is_alpha(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

static bool is_alnum(char c) {
    return is_alpha(c) || is_digit(c);
}

static TokenType get_keyword_type(const char* text) {
    if (strcmp(text, "let") == 0) return TOKEN_LET;
    if (strcmp(text, "fun") == 0) return TOKEN_FUN;
    if (strcmp(text, "if") == 0) return TOKEN_IF;
    if (strcmp(text, "else") == 0) return TOKEN_ELSE;
    if (strcmp(text, "while") == 0) return TOKEN_WHILE;
    if (strcmp(text, "true") == 0) return TOKEN_TRUE;
    if (strcmp(text, "false") == 0) return TOKEN_FALSE;
    if (strcmp(text, "print") == 0) return TOKEN_PRINT;
    if (strcmp(text, "return") == 0) return TOKEN_RETURN;
    return TOKEN_IDENTIFIER;
}

static Token create_token(TokenType type, const char* value, int line, int column) {
    Token token;
    token.type = type;
    token.value = value ? strdup(value) : NULL;
    token.line = line;
    token.column = column;
    return token;
}

Token* tokenize(const char* source, int* token_count) {
    int capacity = 1000;
    Token* tokens = malloc(sizeof(Token) * capacity);
    int count = 0;
    
    int line = 1;
    int column = 1;
    int i = 0;
    
    while (source[i] != '\0') {
        // Resize if needed
        if (count >= capacity - 1) {
            capacity *= 2;
            tokens = realloc(tokens, sizeof(Token) * capacity);
        }
        
        // Skip whitespace (except newlines)
        if (source[i] == ' ' || source[i] == '\t' || source[i] == '\r') {
            if (source[i] == '\t') column += 4;
            else column++;
            i++;
            continue;
        }
        
        // Handle newlines
        if (source[i] == '\n') {
            tokens[count++] = create_token(TOKEN_NEWLINE, NULL, line, column);
            line++;
            column = 1;
            i++;
            continue;
        }
        
        // Skip comments
        if (source[i] == '/' && source[i + 1] == '/') {
            while (source[i] != '\0' && source[i] != '\n') {
                i++;
                column++;
            }
            continue;
        }
          // Numbers
        if (is_digit(source[i])) {
            int start = i;
            bool has_dot = false;
            while (is_digit(source[i]) || (source[i] == '.' && !has_dot)) {
                if (source[i] == '.') {
                    has_dot = true;
                }
                i++;
                column++;
            }
            
            char* number_str = malloc(i - start + 1);
            strncpy(number_str, source + start, i - start);
            number_str[i - start] = '\0';
            
            tokens[count++] = create_token(TOKEN_NUMBER, number_str, line, column - (i - start));
            free(number_str);
            continue;
        }
        
        // Strings
        if (source[i] == '"') {
            int start = ++i; // Skip opening quote
            column++;
            
            while (source[i] != '\0' && source[i] != '"') {
                if (source[i] == '\n') {
                    line++;
                    column = 1;
                } else {
                    column++;
                }
                i++;
            }
            
            if (source[i] == '"') {
                char* string_str = malloc(i - start + 1);
                strncpy(string_str, source + start, i - start);
                string_str[i - start] = '\0';
                
                tokens[count++] = create_token(TOKEN_STRING, string_str, line, column - (i - start + 1));
                free(string_str);
                i++; // Skip closing quote
                column++;
            }
            continue;
        }
        
        // Identifiers and keywords
        if (is_alpha(source[i])) {
            int start = i;
            while (is_alnum(source[i])) {
                i++;
                column++;
            }
            
            char* identifier_str = malloc(i - start + 1);
            strncpy(identifier_str, source + start, i - start);
            identifier_str[i - start] = '\0';
            
            TokenType type = get_keyword_type(identifier_str);
            tokens[count++] = create_token(type, identifier_str, line, column - (i - start));
            free(identifier_str);
            continue;
        }
        
        // Two-character operators
        if (i + 1 < strlen(source)) {
            if (source[i] == '=' && source[i + 1] == '=') {
                tokens[count++] = create_token(TOKEN_EQUAL, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
            if (source[i] == '!' && source[i + 1] == '=') {
                tokens[count++] = create_token(TOKEN_NOT_EQUAL, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
            if (source[i] == '<' && source[i + 1] == '=') {
                tokens[count++] = create_token(TOKEN_LESS_EQUAL, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
            if (source[i] == '>' && source[i + 1] == '=') {
                tokens[count++] = create_token(TOKEN_GREATER_EQUAL, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
            if (source[i] == '&' && source[i + 1] == '&') {
                tokens[count++] = create_token(TOKEN_AND, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
            if (source[i] == '|' && source[i + 1] == '|') {
                tokens[count++] = create_token(TOKEN_OR, NULL, line, column);
                i += 2; column += 2;
                continue;
            }
        }
        
        // Single-character tokens
        switch (source[i]) {
            case '+': tokens[count++] = create_token(TOKEN_PLUS, NULL, line, column); break;
            case '-': tokens[count++] = create_token(TOKEN_MINUS, NULL, line, column); break;
            case '*': tokens[count++] = create_token(TOKEN_MULTIPLY, NULL, line, column); break;
            case '/': tokens[count++] = create_token(TOKEN_DIVIDE, NULL, line, column); break;
            case '=': tokens[count++] = create_token(TOKEN_ASSIGN, NULL, line, column); break;
            case '<': tokens[count++] = create_token(TOKEN_LESS, NULL, line, column); break;
            case '>': tokens[count++] = create_token(TOKEN_GREATER, NULL, line, column); break;
            case '!': tokens[count++] = create_token(TOKEN_NOT, NULL, line, column); break;
            case ';': tokens[count++] = create_token(TOKEN_SEMICOLON, NULL, line, column); break;
            case ',': tokens[count++] = create_token(TOKEN_COMMA, NULL, line, column); break;
            case '(': tokens[count++] = create_token(TOKEN_LEFT_PAREN, NULL, line, column); break;
            case ')': tokens[count++] = create_token(TOKEN_RIGHT_PAREN, NULL, line, column); break;
            case '{': tokens[count++] = create_token(TOKEN_LEFT_BRACE, NULL, line, column); break;
            case '}': tokens[count++] = create_token(TOKEN_RIGHT_BRACE, NULL, line, column); break;
            default:
                printf("Unexpected character '%c' at line %d, column %d\n", source[i], line, column);
                break;
        }
        i++;
        column++;
    }
    
    // Add EOF token
    tokens[count++] = create_token(TOKEN_EOF, NULL, line, column);
    
    *token_count = count;
    return tokens;
}

void free_tokens(Token* tokens, int count) {
    for (int i = 0; i < count; i++) {
        if (tokens[i].value) {
            free(tokens[i].value);
        }
    }
    free(tokens);
}
