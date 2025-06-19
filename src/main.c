#include "yeep.h"

int main(int argc, char* argv[]) {
    printf("Yeep Programming Language v1.0\n");
    
    if (argc == 1) {
        // No arguments - start interactive shell
        printf("Starting interactive shell. Type 'exit' to quit.\n");
        run_shell();
    } else if (argc == 2) {
        // One argument - run file
        run_file(argv[1]);
    } else {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    
    return 0;
}
