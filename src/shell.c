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
    
    // Handle shebang line - skip if it starts with #!
    char* actual_content = content;
    if (length >= 2 && content[0] == '#' && content[1] == '!') {
        // Find the end of the first line
        char* newline = strchr(content, '\n');
        if (newline) {
            actual_content = newline + 1;
        }
    }
    
    // If we skipped the shebang, we need to create a new string
    if (actual_content != content) {
        char* new_content = malloc(strlen(actual_content) + 1);
        strcpy(new_content, actual_content);
        free(content);
        return new_content;
    }
      return content;
}

static void execute_code(const char* source, Environment* env) {
    if (!source || strlen(source) == 0) {
        return;
    }
    
    // Check if the source contains only whitespace
    bool only_whitespace = true;
    for (int i = 0; source[i] != '\0'; i++) {
        if (source[i] != ' ' && source[i] != '\t' && source[i] != '\n' && source[i] != '\r') {
            only_whitespace = false;
            break;
        }
    }
    
    if (only_whitespace) {
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
    int token_count = 0;
    Token* tokens = tokenize(source, &token_count);
    
    if (!tokens || token_count == 0) {
        if (tokens) free_tokens(tokens, token_count);
        return;
    }
    
    // Parse
    ASTNode* ast = parse(tokens, token_count);
    if (!ast) {
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

void run_piped_input(void) {
    Environment* global_env = create_environment(NULL);
    
    // Read all input without prompting
    char* line;
    while ((line = read_line()) != NULL) {
        // Skip empty lines
        if (strlen(line) == 0) {
            free(line);
            continue;
        }
        
        execute_code(line, global_env);
        free(line);
    }
    
    free_environment(global_env);
}
