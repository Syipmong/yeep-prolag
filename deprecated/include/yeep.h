#ifndef YEEP_H
#define YEEP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Platform-specific includes for standard functions
#ifdef _WIN32
#define strdup _strdup
#else
// For POSIX systems, ensure strdup is available
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <unistd.h>
#endif

// Forward declarations
typedef struct Token Token;
typedef struct ASTNode ASTNode;
typedef struct Environment Environment;
typedef struct Value Value;

// Token types
typedef enum {
    TOKEN_EOF,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,
    TOKEN_LET,
    TOKEN_FUN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_PRINT,
    TOKEN_RETURN,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_NOT_EQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LESS_EQUAL,
    TOKEN_GREATER_EQUAL,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_NOT,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_LEFT_PAREN,
    TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE,
    TOKEN_RIGHT_BRACE,
    TOKEN_NEWLINE
} TokenType;

// Token structure
struct Token {
    TokenType type;
    char* value;
    int line;
    int column;
};

// AST Node types
typedef enum {
    AST_NUMBER,
    AST_STRING,
    AST_BOOLEAN,
    AST_IDENTIFIER,
    AST_BINARY_OP,
    AST_UNARY_OP,
    AST_ASSIGNMENT,
    AST_FUNCTION_CALL,
    AST_FUNCTION_DEF,
    AST_IF_STATEMENT,
    AST_WHILE_STATEMENT,
    AST_BLOCK,
    AST_RETURN_STATEMENT,
    AST_PRINT_STATEMENT
} ASTNodeType;

// AST Node structure
struct ASTNode {
    ASTNodeType type;
    union {
        double number;
        char* string;
        bool boolean;
        struct {
            char* name;
        } identifier;
        struct {
            TokenType operator;
            ASTNode* left;
            ASTNode* right;
        } binary_op;
        struct {
            TokenType operator;
            ASTNode* operand;
        } unary_op;
        struct {
            char* variable;
            ASTNode* value;
        } assignment;
        struct {
            char* name;
            ASTNode** arguments;
            int arg_count;
        } function_call;
        struct {
            char* name;
            char** parameters;
            int param_count;
            ASTNode* body;
        } function_def;
        struct {
            ASTNode* condition;
            ASTNode* then_branch;
            ASTNode* else_branch;
        } if_statement;
        struct {
            ASTNode* condition;
            ASTNode* body;
        } while_statement;
        struct {
            ASTNode** statements;
            int statement_count;
        } block;
        struct {
            ASTNode* value;
        } return_statement;
        struct {
            ASTNode* expression;
        } print_statement;
    } data;
};

// Value types
typedef enum {
    VALUE_NUMBER,
    VALUE_STRING,
    VALUE_BOOLEAN,
    VALUE_FUNCTION,
    VALUE_NULL
} ValueType;

// Value structure
struct Value {
    ValueType type;
    union {
        double number;
        char* string;
        bool boolean;
        struct {
            char** parameters;
            int param_count;
            ASTNode* body;
            Environment* closure;
        } function;
    } data;
};

// Environment for variable storage
struct Environment {
    char** names;
    Value* values;
    int count;
    int capacity;
    Environment* parent;
};

// Function prototypes
// Lexer
Token* tokenize(const char* source, int* token_count);
void free_tokens(Token* tokens, int count);

// Parser
ASTNode* parse(Token* tokens, int token_count);
void free_ast(ASTNode* node);

// Interpreter
Value interpret(ASTNode* node, Environment* env);
Environment* create_environment(Environment* parent);
void free_environment(Environment* env);

// Shell
void run_shell(void);
void run_piped_input(void);
void run_file(const char* filename);

// Utilities
void print_value(Value value);
Value create_number(double num);
Value create_string(const char* str);
Value create_boolean(bool val);
Value create_null(void);

#endif // YEEP_H
