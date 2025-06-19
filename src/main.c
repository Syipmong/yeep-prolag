#include "yeep.h"
#include <string.h>
#ifdef _WIN32
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

#define YEEP_VERSION "1.0.0"

void print_version() {
    printf("Yeep Programming Language v%s\n", YEEP_VERSION);
    printf("Copyright (c) 2025 Yipmong Said\n");
    printf("Licensed under MIT License\n");
}

void print_help(const char* program_name) {
    printf("Yeep Programming Language v%s\n\n", YEEP_VERSION);
    printf("Usage: %s [options] [script]\n\n", program_name);
    printf("Options:\n");
    printf("  -h, --help     Show this help message\n");
    printf("  -v, --version  Show version information\n");
    printf("  -i, --repl     Force interactive mode (REPL)\n");
    printf("\n");
    printf("Examples:\n");
    printf("  %s                    Start interactive shell\n", program_name);
    printf("  %s script.yeep        Run a Yeep script\n", program_name);
    printf("  %s -i                 Force interactive mode\n", program_name);
    printf("  %s --version          Show version\n", program_name);
}

int main(int argc, char* argv[]) {
    // Parse command line arguments
    int interactive_mode = 0;
    char* script_file = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            return 0;
        } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
            print_version();
            return 0;
        } else if (strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--repl") == 0) {
            interactive_mode = 1;
        } else if (argv[i][0] == '-') {
            printf("Unknown option: %s\n", argv[i]);
            printf("Use '%s --help' for usage information.\n", argv[0]);
            return 1;
        } else if (script_file == NULL) {
            script_file = argv[i];
        } else {
            printf("Too many arguments.\n");
            printf("Use '%s --help' for usage information.\n", argv[0]);
            return 1;
        }
    }    // Execute based on arguments
    if (script_file != NULL) {
        // Run script file
        run_file(script_file);
    } else if (interactive_mode || isatty(fileno(stdin))) {
        // Interactive shell mode (forced or stdin is a terminal)
        printf("Yeep Programming Language v%s\n", YEEP_VERSION);
        printf("Starting interactive shell. Type 'exit' to quit or 'help' for commands.\n");
        run_shell();
    } else {
        // Piped input mode - read all input and execute without prompts
        printf("Yeep Programming Language v%s\n", YEEP_VERSION);
        printf("Starting interactive shell. Type 'exit' to quit or 'help' for commands.\n");
        run_piped_input();
    }
    
    return 0;
}
