#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include "Lexer.hpp"
#include "Interpreter.hpp"

// ANSI color codes for better REPL experience
#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define isatty _isatty
    #define fileno _fileno
#else
    #include <unistd.h>
#endif

namespace {
    bool supportsColors() {
        #ifdef _WIN32
            // Enable ANSI colors on Windows 10+
            HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
            DWORD dwMode = 0;
            GetConsoleMode(hOut, &dwMode);
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
            return true;
        #else
            return isatty(fileno(stdout));
        #endif
    }

    const std::string RESET = "\033[0m";
    const std::string BOLD = "\033[1m";
    const std::string GREEN = "\033[32m";
    const std::string BLUE = "\033[34m";
    const std::string CYAN = "\033[36m";
    const std::string YELLOW = "\033[33m";
    const std::string RED = "\033[31m";
    const std::string MAGENTA = "\033[35m";

    std::string colorize(const std::string& text, const std::string& color) {
        static bool colors = supportsColors();
        return colors ? (color + text + RESET) : text;
    }
}

void printWelcome() {
    std::cout << colorize("╔══════════════════════════════════════════════════════════════╗", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("               🎯 Yeep Programming Language v2.0.3            ", BOLD) << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << "                                                              " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("  Interactive REPL - Read, Evaluate, Print, Loop              ", GREEN) << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << "                                                              " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << "  Commands:                                                   " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    help     ", YELLOW) << "- Show this help message                      " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    version  ", YELLOW) << "- Show version information                    " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    clear    ", YELLOW) << "- Clear the screen                            " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    vars     ", YELLOW) << "- Show all variables                          " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    funcs    ", YELLOW) << "- Show all functions                          " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    examples ", YELLOW) << "- Show example code                           " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << colorize("    exit     ", YELLOW) << "- Exit the REPL                               " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << "                                                              " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("║", CYAN) << "  Type Yeep expressions and press Enter to evaluate them.   " << colorize("║", CYAN) << std::endl;
    std::cout << colorize("╚══════════════════════════════════════════════════════════════╝", CYAN) << std::endl;
    std::cout << std::endl;
}

void printHelp() {
    std::cout << colorize("\n📚 Yeep Language Quick Reference:", BOLD) << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("Variables:", CYAN) << std::endl;
    std::cout << "  let x = 42;                    // Number" << std::endl;
    std::cout << "  let name = \"Yeep\";             // String" << std::endl;
    std::cout << "  let flag = true;               // Boolean" << std::endl;
    std::cout << "  let arr = [1, 2, 3];           // Array" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("Functions:", CYAN) << std::endl;
    std::cout << "  fun greet(name) {" << std::endl;
    std::cout << "      return \"Hello, \" + name + \"!\";" << std::endl;
    std::cout << "  }" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("Built-in Functions:", CYAN) << std::endl;
    std::cout << "  print(value)                   // Output to console" << std::endl;
    std::cout << "  str(value)                     // Convert to string" << std::endl;
    std::cout << "  sqrt(16)                       // Math functions" << std::endl;
    std::cout << "  length(\"hello\")                // String/array length" << std::endl;
    std::cout << "  max(1, 5, 3)                   // Maximum value" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("Control Flow:", CYAN) << std::endl;
    std::cout << "  if (x > 0) { print(\"positive\"); }" << std::endl;
    std::cout << "  while (i < 10) { i = i + 1; }" << std::endl;
    std::cout << "  for (let i = 0; i < 5; i = i + 1) { print(i); }" << std::endl;
    std::cout << std::endl;
}

void printVersion() {
    std::cout << colorize("\n🎯 Yeep Programming Language", BOLD) << std::endl;
    std::cout << colorize("Version: ", CYAN) << "2.0.3" << std::endl;
    std::cout << colorize("Built: ", CYAN) << __DATE__ << " " << __TIME__ << std::endl;
    std::cout << colorize("Architecture: ", CYAN) << "Modern C++17" << std::endl;
    std::cout << colorize("Platform: ", CYAN) << 
        #ifdef _WIN32
            "Windows"
        #elif defined(__linux__)
            "Linux"
        #elif defined(__APPLE__)
            "macOS"
        #else
            "Unknown"
        #endif
        << std::endl;
    std::cout << colorize("Repository: ", CYAN) << "https://github.com/Syipmong/yeep-prolag" << std::endl;
    std::cout << std::endl;
}

void printExamples() {
    std::cout << colorize("\n✨ Yeep Code Examples:", BOLD) << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("1. Basic Calculator:", YELLOW) << std::endl;
    std::cout << "   let a = 10;" << std::endl;
    std::cout << "   let b = 5;" << std::endl;
    std::cout << "   print(\"Sum: \" + str(a + b));" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("2. Function with Logic:", YELLOW) << std::endl;
    std::cout << "   fun isEven(n) {" << std::endl;
    std::cout << "       return n % 2 == 0;" << std::endl;
    std::cout << "   }" << std::endl;
    std::cout << "   print(isEven(4));" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("3. Array Processing:", YELLOW) << std::endl;
    std::cout << "   let numbers = [1, 2, 3, 4, 5];" << std::endl;
    std::cout << "   print(\"Length: \" + str(size(numbers)));" << std::endl;
    std::cout << "   print(\"First: \" + str(get(numbers, 0)));" << std::endl;
    std::cout << std::endl;
    
    std::cout << colorize("4. Factorial Function:", YELLOW) << std::endl;
    std::cout << "   fun factorial(n) {" << std::endl;
    std::cout << "       if (n <= 1) { return 1; }" << std::endl;
    std::cout << "       return n * factorial(n - 1);" << std::endl;
    std::cout << "   }" << std::endl;
    std::cout << "   print(factorial(5));" << std::endl;
    std::cout << std::endl;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void runRepl() {
    printWelcome();
    
    yeep::Interpreter interpreter;
    std::string input;
    int commandCount = 0;
    
    while (true) {
        // Show prompt
        std::cout << colorize("yeep", GREEN) << colorize("> ", BLUE);
        
        // Get input line
        if (!std::getline(std::cin, input)) {
            // EOF reached (Ctrl+D or Ctrl+Z)
            std::cout << std::endl << colorize("Goodbye! Thanks for using Yeep! 👋", YELLOW) << std::endl;
            break;
        }
        
        // Trim whitespace
        input.erase(0, input.find_first_not_of(" \t\n\r"));
        input.erase(input.find_last_not_of(" \t\n\r") + 1);
        
        // Skip empty lines
        if (input.empty()) {
            continue;
        }
        
        commandCount++;
        
        // Handle special commands
        if (input == "help") {
            printHelp();
            continue;
        } else if (input == "version") {
            printVersion();
            continue;
        } else if (input == "clear") {
            clearScreen();
            printWelcome();
            continue;
        } else if (input == "examples") {
            printExamples();
            continue;
        } else if (input == "exit" || input == "quit") {
            std::cout << colorize("Goodbye! Thanks for using Yeep! 👋", YELLOW) << std::endl;
            break;
        } else if (input == "vars") {
            std::cout << colorize("🔍 Variable inspection not yet implemented", YELLOW) << std::endl;
            continue;
        } else if (input == "funcs") {
            std::cout << colorize("🔍 Function inspection not yet implemented", YELLOW) << std::endl;
            continue;
        }
        
        // Add semicolon if missing (for convenience)
        if (!input.empty() && input.back() != ';' && input.back() != '}') {
            input += ";";
        }
        
        try {
            // Tokenize and interpret
            yeep::Lexer lexer(input);
            auto tokens = lexer.tokenize();
            
            if (!tokens.empty()) {
                interpreter.interpret(tokens);
            }
        } catch (const std::exception& e) {
            std::cout << colorize("❌ Error: ", RED) << e.what() << std::endl;
        }
    }
}

int runFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << colorize("❌ Error: ", RED) << "Could not open file: " << filename << std::endl;
        return 1;
    }

    std::string source((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();

    try {
        yeep::Lexer lexer(source);
        auto tokens = lexer.tokenize();
        
        yeep::Interpreter interpreter;
        interpreter.interpret(tokens);
    } catch (const std::exception& e) {
        std::cerr << colorize("❌ Error: ", RED) << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}

void printUsage(const char* programName) {
    std::cout << colorize("🎯 Yeep Programming Language v2.0.3", BOLD) << std::endl;
    std::cout << std::endl;
    std::cout << colorize("Usage:", CYAN) << std::endl;
    std::cout << "  " << programName << "                    " << colorize("# Start interactive REPL", GREEN) << std::endl;
    std::cout << "  " << programName << " <filename>          " << colorize("# Run Yeep script file", GREEN) << std::endl;
    std::cout << "  " << programName << " --help              " << colorize("# Show this help", GREEN) << std::endl;
    std::cout << "  " << programName << " --version           " << colorize("# Show version info", GREEN) << std::endl;
    std::cout << std::endl;
    std::cout << colorize("Examples:", CYAN) << std::endl;
    std::cout << "  " << programName << "                    " << colorize("# Start REPL", YELLOW) << std::endl;
    std::cout << "  " << programName << " script.yeep        " << colorize("# Run script.yeep", YELLOW) << std::endl;
    std::cout << "  " << programName << " examples/hello.yeep " << colorize("# Run example", YELLOW) << std::endl;
    std::cout << std::endl;
}

int main(int argc, char* argv[]) {
    // Handle command line arguments
    if (argc == 1) {
        // No arguments - start REPL
        runRepl();
        return 0;
    } else if (argc == 2) {
        std::string arg = argv[1];
        
        if (arg == "--help" || arg == "-h") {
            printUsage(argv[0]);
            return 0;
        } else if (arg == "--version" || arg == "-v") {
            printVersion();
            return 0;
        } else {
            // Assume it's a filename
            return runFile(arg);
        }
    } else {
        std::cerr << colorize("❌ Error: ", RED) << "Too many arguments" << std::endl;
        printUsage(argv[0]);
        return 1;
    }
}
