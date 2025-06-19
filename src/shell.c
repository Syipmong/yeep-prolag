#include "yeep.h"

static char* read_line(void) {
    int capacity = 256;
    char* line = malloc(capacity);
    int length = 0;
    int c;
    
    while (true) {
        c = getchar();
        
        if (c == EOF) {
            // If EOF occurs at the beginning of input, return NULL to signal end of input
            if (length == 0) {
                free(line);
                return NULL;
            }
            // If EOF occurs after some input, treat it like a newline
            line[length] = '\0';
            return line;
        } else if (c == '\n') {
            line[length] = '\0';
            return line;
        } else {
            line[length] = c;
        }
        
        length++;
        
        if (length >= capacity) {
            capacity *= 2;
            line = realloc(line, capacity);
        }
    }
}

static char* read_file_contents(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* content = malloc(length + 1);
    fread(content, 1, length, file);
    content[length] = '\0';
    
    fclose(file);
    return content;
}

static void execute_code(const char* source, Environment* env) {
    if (strlen(source) == 0) {
        return;
    }
    
    // Check for special shell commands
    if (strcmp(source, "exit") == 0 || strcmp(source, "quit") == 0) {
        printf("Goodbye!\n");
        exit(0);
    }
    
    if (strcmp(source, "help") == 0) {
        printf("Yeep Programming Language Commands:\n");
        printf("  help    - Show this help message\n");
        printf("  exit    - Exit the shell\n");
        printf("  quit    - Exit the shell\n");
        printf("\nLanguage Features:\n");
        printf("  Variables: let x = 42;\n");
        printf("  Functions: fun greet(name) { print(\"Hello, \" + name); }\n");
        printf("  Control Flow: if, while\n");
        printf("  Operators: +, -, *, /, ==, !=, <, >, <=, >=, &&, ||\n");
        printf("  Built-in: print(expression)\n");
        return;
    }
    
    // Tokenize
    int token_count;
    Token* tokens = tokenize(source, &token_count);
    
    if (!tokens) {
        printf("Error: Failed to tokenize input\n");
        return;
    }
    
    // Parse
    ASTNode* ast = parse(tokens, token_count);
    if (!ast) {
        printf("Error: Failed to parse input\n");
        free_tokens(tokens, token_count);
        return;
    }
    
    // Interpret
    Value result = interpret(ast, env);
    
    // Print result if it's not null and not from a statement
    if (result.type != VALUE_NULL) {
        print_value(result);
        printf("\n");
    }
    
    // Cleanup
    free_ast(ast);
    free_tokens(tokens, token_count);
}

void run_shell(void) {
    Environment* global_env = create_environment(NULL);
    
    printf("Yeep> ");
    
    while (true) {
        char* line = read_line();
        
        if (!line) {
            printf("\nGoodbye!\n");
            break;
        }
        
        // Skip empty lines
        if (strlen(line) == 0) {
            free(line);
            printf("Yeep> ");
            continue;
        }
        
        execute_code(line, global_env);
        
        free(line);
        printf("Yeep> ");
    }
    
    free_environment(global_env);
}

void run_file(const char* filename) {
    char* source = read_file_contents(filename);
    if (!source) {
        exit(1);
    }
    
    Environment* global_env = create_environment(NULL);
    execute_code(source, global_env);
    
    free(source);
    free_environment(global_env);
}
