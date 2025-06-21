#include "yeep.h"

typedef struct Parser {
    Token* tokens;
    int token_count;
    int current;
} Parser;

static Parser* create_parser(Token* tokens, int token_count) {
    Parser* parser = malloc(sizeof(Parser));
    parser->tokens = tokens;
    parser->token_count = token_count;
    parser->current = 0;
    return parser;
}

static Token* current_token(Parser* parser) {
    if (parser->current >= parser->token_count) {
        return &parser->tokens[parser->token_count - 1]; // EOF token
    }
    return &parser->tokens[parser->current];
}

static Token* advance(Parser* parser) {
    if (parser->current < parser->token_count - 1) {
        parser->current++;
    }
    return current_token(parser);
}

static bool match(Parser* parser, TokenType type) {
    if (current_token(parser)->type == type) {
        advance(parser);
        return true;
    }
    return false;
}

static bool check(Parser* parser, TokenType type) {
    return current_token(parser)->type == type;
}

static void skip_newlines(Parser* parser) {
    while (match(parser, TOKEN_NEWLINE)) {
        // Skip newlines
    }
}

// Forward declarations
static ASTNode* parse_expression(Parser* parser);
static ASTNode* parse_statement(Parser* parser);
static ASTNode* parse_block(Parser* parser);

static ASTNode* create_ast_node(ASTNodeType type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = type;
    return node;
}

static ASTNode* parse_primary(Parser* parser) {
    skip_newlines(parser);
    
    if (match(parser, TOKEN_NUMBER)) {
        ASTNode* node = create_ast_node(AST_NUMBER);
        node->data.number = atof(parser->tokens[parser->current - 1].value);
        return node;
    }
    
    if (match(parser, TOKEN_STRING)) {
        ASTNode* node = create_ast_node(AST_STRING);
        node->data.string = strdup(parser->tokens[parser->current - 1].value);
        return node;
    }
    
    if (match(parser, TOKEN_TRUE)) {
        ASTNode* node = create_ast_node(AST_BOOLEAN);
        node->data.boolean = true;
        return node;
    }
    
    if (match(parser, TOKEN_FALSE)) {
        ASTNode* node = create_ast_node(AST_BOOLEAN);
        node->data.boolean = false;
        return node;
    }
    
    if (match(parser, TOKEN_IDENTIFIER)) {
        char* name = strdup(parser->tokens[parser->current - 1].value);
        
        // Check for function call
        if (match(parser, TOKEN_LEFT_PAREN)) {
            ASTNode* node = create_ast_node(AST_FUNCTION_CALL);
            node->data.function_call.name = name;
            node->data.function_call.arguments = NULL;
            node->data.function_call.arg_count = 0;
            
            if (!check(parser, TOKEN_RIGHT_PAREN)) {
                int capacity = 10;
                node->data.function_call.arguments = malloc(sizeof(ASTNode*) * capacity);
                
                do {
                    if (node->data.function_call.arg_count >= capacity) {
                        capacity *= 2;
                        node->data.function_call.arguments = realloc(
                            node->data.function_call.arguments, 
                            sizeof(ASTNode*) * capacity
                        );
                    }
                    node->data.function_call.arguments[node->data.function_call.arg_count++] = 
                        parse_expression(parser);
                } while (match(parser, TOKEN_COMMA));
            }
            
            if (!match(parser, TOKEN_RIGHT_PAREN)) {
                printf("Expected ')' after function arguments\n");
                exit(1);
            }
            
            return node;
        } else {
            // Regular identifier
            ASTNode* node = create_ast_node(AST_IDENTIFIER);
            node->data.identifier.name = name;
            return node;
        }
    }
    
    if (match(parser, TOKEN_LEFT_PAREN)) {
        ASTNode* expr = parse_expression(parser);
        if (!match(parser, TOKEN_RIGHT_PAREN)) {
            printf("Expected ')' after expression\n");
            exit(1);
        }
        return expr;
    }
    
    printf("Unexpected token in expression\n");
    exit(1);
}

static ASTNode* parse_unary(Parser* parser) {
    if (match(parser, TOKEN_NOT) || match(parser, TOKEN_MINUS)) {
        ASTNode* node = create_ast_node(AST_UNARY_OP);
        node->data.unary_op.operator = parser->tokens[parser->current - 1].type;
        node->data.unary_op.operand = parse_unary(parser);
        return node;
    }
    
    return parse_primary(parser);
}

static ASTNode* parse_factor(Parser* parser) {
    ASTNode* expr = parse_unary(parser);
    
    while (match(parser, TOKEN_MULTIPLY) || match(parser, TOKEN_DIVIDE)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_unary(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_term(Parser* parser) {
    ASTNode* expr = parse_factor(parser);
    
    while (match(parser, TOKEN_PLUS) || match(parser, TOKEN_MINUS)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_factor(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_comparison(Parser* parser) {
    ASTNode* expr = parse_term(parser);
    
    while (match(parser, TOKEN_GREATER) || match(parser, TOKEN_GREATER_EQUAL) ||
           match(parser, TOKEN_LESS) || match(parser, TOKEN_LESS_EQUAL)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_term(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_equality(Parser* parser) {
    ASTNode* expr = parse_comparison(parser);
    
    while (match(parser, TOKEN_NOT_EQUAL) || match(parser, TOKEN_EQUAL)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_comparison(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_logical_and(Parser* parser) {
    ASTNode* expr = parse_equality(parser);
    
    while (match(parser, TOKEN_AND)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_equality(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_logical_or(Parser* parser) {
    ASTNode* expr = parse_logical_and(parser);
    
    while (match(parser, TOKEN_OR)) {
        TokenType operator = parser->tokens[parser->current - 1].type;
        ASTNode* right = parse_logical_and(parser);
        
        ASTNode* binary = create_ast_node(AST_BINARY_OP);
        binary->data.binary_op.operator = operator;
        binary->data.binary_op.left = expr;
        binary->data.binary_op.right = right;
        
        expr = binary;
    }
    
    return expr;
}

static ASTNode* parse_assignment(Parser* parser) {
    ASTNode* expr = parse_logical_or(parser);
    
    if (match(parser, TOKEN_ASSIGN)) {
        if (expr->type != AST_IDENTIFIER) {
            printf("Invalid assignment target\n");
            exit(1);
        }
        
        ASTNode* value = parse_assignment(parser);
        ASTNode* assignment = create_ast_node(AST_ASSIGNMENT);
        assignment->data.assignment.variable = strdup(expr->data.identifier.name);
        assignment->data.assignment.value = value;
        
        free_ast(expr);
        return assignment;
    }
    
    return expr;
}

static ASTNode* parse_expression(Parser* parser) {
    return parse_assignment(parser);
}

static ASTNode* parse_block(Parser* parser) {
    ASTNode* block = create_ast_node(AST_BLOCK);
    block->data.block.statements = NULL;
    block->data.block.statement_count = 0;
    
    skip_newlines(parser);
    
    if (!match(parser, TOKEN_LEFT_BRACE)) {
        printf("Expected '{' to start block\n");
        exit(1);
    }
    
    skip_newlines(parser);
    
    int capacity = 10;
    block->data.block.statements = malloc(sizeof(ASTNode*) * capacity);
    
    while (!check(parser, TOKEN_RIGHT_BRACE) && !check(parser, TOKEN_EOF)) {
        if (block->data.block.statement_count >= capacity) {
            capacity *= 2;
            block->data.block.statements = realloc(
                block->data.block.statements, 
                sizeof(ASTNode*) * capacity
            );
        }
        
        block->data.block.statements[block->data.block.statement_count++] = 
            parse_statement(parser);
        skip_newlines(parser);
    }
    
    if (!match(parser, TOKEN_RIGHT_BRACE)) {
        printf("Expected '}' to end block\n");
        exit(1);
    }
    
    return block;
}

static ASTNode* parse_statement(Parser* parser) {
    skip_newlines(parser);
    
    // Variable declaration
    if (match(parser, TOKEN_LET)) {
        if (!match(parser, TOKEN_IDENTIFIER)) {
            printf("Expected identifier after 'let'\n");
            exit(1);
        }
        
        char* name = strdup(parser->tokens[parser->current - 1].value);
        
        if (!match(parser, TOKEN_ASSIGN)) {
            printf("Expected '=' after variable name\n");
            exit(1);
        }
        
        ASTNode* value = parse_expression(parser);
        
        if (!match(parser, TOKEN_SEMICOLON)) {
            printf("Expected ';' after variable declaration\n");
            exit(1);
        }
        
        ASTNode* assignment = create_ast_node(AST_ASSIGNMENT);
        assignment->data.assignment.variable = name;
        assignment->data.assignment.value = value;
        
        return assignment;
    }
    
    // Function definition
    if (match(parser, TOKEN_FUN)) {
        if (!match(parser, TOKEN_IDENTIFIER)) {
            printf("Expected function name\n");
            exit(1);
        }
        
        char* name = strdup(parser->tokens[parser->current - 1].value);
        
        if (!match(parser, TOKEN_LEFT_PAREN)) {
            printf("Expected '(' after function name\n");
            exit(1);
        }
        
        ASTNode* func_def = create_ast_node(AST_FUNCTION_DEF);
        func_def->data.function_def.name = name;
        func_def->data.function_def.parameters = NULL;
        func_def->data.function_def.param_count = 0;
        
        if (!check(parser, TOKEN_RIGHT_PAREN)) {
            int capacity = 10;
            func_def->data.function_def.parameters = malloc(sizeof(char*) * capacity);
            
            do {
                if (!match(parser, TOKEN_IDENTIFIER)) {
                    printf("Expected parameter name\n");
                    exit(1);
                }
                
                if (func_def->data.function_def.param_count >= capacity) {
                    capacity *= 2;
                    func_def->data.function_def.parameters = realloc(
                        func_def->data.function_def.parameters, 
                        sizeof(char*) * capacity
                    );
                }
                
                func_def->data.function_def.parameters[func_def->data.function_def.param_count++] = 
                    strdup(parser->tokens[parser->current - 1].value);
            } while (match(parser, TOKEN_COMMA));
        }
        
        if (!match(parser, TOKEN_RIGHT_PAREN)) {
            printf("Expected ')' after parameters\n");
            exit(1);
        }
        
        func_def->data.function_def.body = parse_block(parser);
        
        return func_def;
    }
    
    // Print statement
    if (match(parser, TOKEN_PRINT)) {
        if (!match(parser, TOKEN_LEFT_PAREN)) {
            printf("Expected '(' after 'print'\n");
            exit(1);
        }
        
        ASTNode* expr = parse_expression(parser);
        
        if (!match(parser, TOKEN_RIGHT_PAREN)) {
            printf("Expected ')' after print expression\n");
            exit(1);
        }
        
        if (!match(parser, TOKEN_SEMICOLON)) {
            printf("Expected ';' after print statement\n");
            exit(1);
        }
        
        ASTNode* print_stmt = create_ast_node(AST_PRINT_STATEMENT);
        print_stmt->data.print_statement.expression = expr;
        
        return print_stmt;
    }
    
    // Return statement
    if (match(parser, TOKEN_RETURN)) {
        ASTNode* return_stmt = create_ast_node(AST_RETURN_STATEMENT);
        
        if (!check(parser, TOKEN_SEMICOLON)) {
            return_stmt->data.return_statement.value = parse_expression(parser);
        } else {
            return_stmt->data.return_statement.value = NULL;
        }
        
        if (!match(parser, TOKEN_SEMICOLON)) {
            printf("Expected ';' after return statement\n");
            exit(1);
        }
        
        return return_stmt;
    }
    
    // If statement
    if (match(parser, TOKEN_IF)) {
        if (!match(parser, TOKEN_LEFT_PAREN)) {
            printf("Expected '(' after 'if'\n");
            exit(1);
        }
        
        ASTNode* condition = parse_expression(parser);
        
        if (!match(parser, TOKEN_RIGHT_PAREN)) {
            printf("Expected ')' after if condition\n");
            exit(1);
        }
        
        ASTNode* then_branch = parse_block(parser);
        ASTNode* else_branch = NULL;
        
        skip_newlines(parser);
        if (match(parser, TOKEN_ELSE)) {
            else_branch = parse_block(parser);
        }
        
        ASTNode* if_stmt = create_ast_node(AST_IF_STATEMENT);
        if_stmt->data.if_statement.condition = condition;
        if_stmt->data.if_statement.then_branch = then_branch;
        if_stmt->data.if_statement.else_branch = else_branch;
        
        return if_stmt;
    }
    
    // While statement
    if (match(parser, TOKEN_WHILE)) {
        if (!match(parser, TOKEN_LEFT_PAREN)) {
            printf("Expected '(' after 'while'\n");
            exit(1);
        }
        
        ASTNode* condition = parse_expression(parser);
        
        if (!match(parser, TOKEN_RIGHT_PAREN)) {
            printf("Expected ')' after while condition\n");
            exit(1);
        }
        
        ASTNode* body = parse_block(parser);
        
        ASTNode* while_stmt = create_ast_node(AST_WHILE_STATEMENT);
        while_stmt->data.while_statement.condition = condition;
        while_stmt->data.while_statement.body = body;
        
        return while_stmt;
    }
    
    // Block statement
    if (check(parser, TOKEN_LEFT_BRACE)) {
        return parse_block(parser);
    }
    
    // Expression statement
    ASTNode* expr = parse_expression(parser);
    if (!match(parser, TOKEN_SEMICOLON)) {
        printf("Expected ';' after expression\n");
        exit(1);
    }
    
    return expr;
}

ASTNode* parse(Token* tokens, int token_count) {
    Parser* parser = create_parser(tokens, token_count);
    
    ASTNode* program = create_ast_node(AST_BLOCK);
    program->data.block.statements = NULL;
    program->data.block.statement_count = 0;
    
    int capacity = 100;
    program->data.block.statements = malloc(sizeof(ASTNode*) * capacity);
    
    skip_newlines(parser);
    
    while (!check(parser, TOKEN_EOF)) {
        if (program->data.block.statement_count >= capacity) {
            capacity *= 2;
            program->data.block.statements = realloc(
                program->data.block.statements, 
                sizeof(ASTNode*) * capacity
            );
        }
        
        program->data.block.statements[program->data.block.statement_count++] = 
            parse_statement(parser);
        skip_newlines(parser);
    }
    
    free(parser);
    return program;
}

void free_ast(ASTNode* node) {
    if (!node) return;
    
    switch (node->type) {
        case AST_STRING:
            free(node->data.string);
            break;
        case AST_IDENTIFIER:
            free(node->data.identifier.name);
            break;
        case AST_BINARY_OP:
            free_ast(node->data.binary_op.left);
            free_ast(node->data.binary_op.right);
            break;
        case AST_UNARY_OP:
            free_ast(node->data.unary_op.operand);
            break;
        case AST_ASSIGNMENT:
            free(node->data.assignment.variable);
            free_ast(node->data.assignment.value);
            break;
        case AST_FUNCTION_CALL:
            free(node->data.function_call.name);
            for (int i = 0; i < node->data.function_call.arg_count; i++) {
                free_ast(node->data.function_call.arguments[i]);
            }
            free(node->data.function_call.arguments);
            break;
        case AST_FUNCTION_DEF:
            free(node->data.function_def.name);
            for (int i = 0; i < node->data.function_def.param_count; i++) {
                free(node->data.function_def.parameters[i]);
            }
            free(node->data.function_def.parameters);
            free_ast(node->data.function_def.body);
            break;
        case AST_IF_STATEMENT:
            free_ast(node->data.if_statement.condition);
            free_ast(node->data.if_statement.then_branch);
            free_ast(node->data.if_statement.else_branch);
            break;
        case AST_WHILE_STATEMENT:
            free_ast(node->data.while_statement.condition);
            free_ast(node->data.while_statement.body);
            break;
        case AST_BLOCK:
            for (int i = 0; i < node->data.block.statement_count; i++) {
                free_ast(node->data.block.statements[i]);
            }
            free(node->data.block.statements);
            break;
        case AST_RETURN_STATEMENT:
            free_ast(node->data.return_statement.value);
            break;
        case AST_PRINT_STATEMENT:
            free_ast(node->data.print_statement.expression);
            break;
        default:
            // Numbers and booleans don't need special cleanup
            break;
    }
    
    free(node);
}
