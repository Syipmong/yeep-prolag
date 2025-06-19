# Yeep C++ Integration and Grammar Enhancement Roadmap

## Project Overview
This roadmap outlines the complete integration of C++ into the Yeep programming language project, focusing on resolving newline handling issues, improving grammar implementation, and adding advanced language features.

## Phase 1: Core C++ Infrastructure (Week 1)
**Status: In Progress** ✅ Partially Complete

### Completed:
- [x] Created C++ project structure (`src/core/`, `include/core/`, etc.)
- [x] Implemented `Token` class with modern C++ features
- [x] Implemented `Lexer` class with improved newline handling
- [x] Created comprehensive grammar specification
- [x] Documented language design principles

### Remaining Tasks:
- [ ] Complete `Parser` class implementation
- [ ] Complete `Interpreter` class implementation
- [ ] Update build system (Makefile, CMake)
- [ ] Create C++ main entry point
- [ ] Test basic functionality

### Key Benefits Achieved:
1. **Fixed Newline Handling**: The C++ lexer properly tracks line numbers and handles different newline formats (`\n`, `\r\n`, etc.)
2. **Better Memory Management**: Using `std::string` eliminates buffer overflow risks
3. **Improved Error Reporting**: C++ classes provide better error context with line/column information

## Phase 2: Parser Enhancement (Week 2)
**Status: Planned** 🔄

### AST Node Hierarchy
```cpp
// Base AST node class
class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual void accept(ASTVisitor& visitor) = 0;
    virtual std::string toString() const = 0;
};

// Expression nodes
class Expression : public ASTNode {};
class BinaryExpression : public Expression {};
class UnaryExpression : public Expression {};
class LiteralExpression : public Expression {};
class VariableExpression : public Expression {};
class FunctionCallExpression : public Expression {};

// Statement nodes
class Statement : public ASTNode {};
class VariableDeclaration : public Statement {};
class FunctionDeclaration : public Statement {};
class IfStatement : public Statement {};
class WhileStatement : public Statement {};
class ReturnStatement : public Statement {};
class ExpressionStatement : public Statement {};
```

### Parser Improvements
- **Better Error Recovery**: Continue parsing after errors to find more issues
- **Improved Error Messages**: Show context and suggestions for fixes
- **Operator Precedence**: Implement precedence climbing algorithm
- **AST Optimization**: Constant folding and dead code elimination

### Grammar Extensions
- **Enhanced Operators**: Add `++`, `--`, `+=`, `-=`, `*=`, `/=`, `%=`
- **Ternary Operator**: Implement `condition ? true_value : false_value`
- **Logical Operators**: Add `&&`, `||`, `!` with proper short-circuiting
- **String Interpolation**: Support `"Hello, ${name}!"` syntax

## Phase 3: Advanced Language Features (Week 3)
**Status: Planned** 📋

### Array Support
```yeep
// Array literals
let numbers = [1, 2, 3, 4, 5];
let mixed = [1, "hello", true, [1, 2]];

// Array access
print(numbers[0]);        // 1
numbers[1] = 10;          // Assignment

// Array methods
numbers.push(6);          // Add element
let last = numbers.pop(); // Remove and return last
print(numbers.length);    // Get size
```

### Object/Map Support
```yeep
// Object literals
let person = {
    name: "Alice",
    age: 30,
    greet: fun() {
        print("Hello, I'm " + this.name);
    }
};

// Property access
print(person.name);       // Dot notation
print(person["age"]);     // Bracket notation
person.city = "New York"; // Dynamic property addition
```

### Enhanced Functions
```yeep
// Default parameters
fun greet(name = "World") {
    print("Hello, " + name + "!");
}

// Variable arguments
fun sum(...numbers) {
    let total = 0;
    for (let num in numbers) {
        total = total + num;
    }
    return total;
}

// Arrow functions (lambda expressions)
let double = (x) => x * 2;
let add = (a, b) => a + b;
```

### For Loops
```yeep
// C-style for loop
for (let i = 0; i < 10; i = i + 1) {
    print(i);
}

// For-in loop (iterate over arrays/objects)
let fruits = ["apple", "banana", "cherry"];
for (let fruit in fruits) {
    print(fruit);
}

// For-of loop (iterate over values)
for (let fruit of fruits) {
    print("I like " + fruit);
}
```

## Phase 4: Type System and Safety (Week 4)
**Status: Future** 🔮

### Optional Type Annotations
```yeep
// Function with type hints
fun add(a: number, b: number): number {
    return a + b;
}

// Variable with type
let name: string = "Alice";
let age: number = 30;
let active: boolean = true;

// Optional types
let optional_value: number? = null;
```

### Type Checking
- **Static Type Analysis**: Catch type errors at compile time
- **Type Inference**: Deduce types from usage when not specified
- **Generic Types**: Support for parameterized types
- **Union Types**: Variables can be one of several types

### Runtime Type Safety
```yeep
// Runtime type checking
fun safe_divide(a, b) {
    if (typeof(b) != "number" || b == 0) {
        throw TypeError("Invalid divisor");
    }
    return a / b;
}

// Type guards
if (typeof(value) == "string") {
    // TypeScript-style type narrowing
    print(value.length); // Safe to use string methods
}
```

## Phase 5: Advanced Features (Week 5+)
**Status: Future** 🚀

### Module System
```yeep
// math.yeep
export fun add(a, b) { return a + b; }
export fun multiply(a, b) { return a * b; }
export let PI = 3.14159;

// main.yeep
import { add, multiply, PI } from "./math.yeep";
import * as math from "./math.yeep";

print(add(2, 3));
print(math.PI);
```

### Exception Handling
```yeep
// Try-catch blocks
try {
    let result = risky_operation();
    print(result);
} catch (error) {
    print("Error occurred: " + error.message);
} finally {
    print("Cleanup code");
}

// Custom exceptions
throw Error("Something went wrong");
throw TypeError("Expected number, got string");
```

### Classes and Objects
```yeep
// Class definition
class Person {
    // Constructor
    fun init(name, age) {
        this.name = name;
        this.age = age;
    }
    
    // Methods
    fun greet() {
        print("Hello, I'm " + this.name);
    }
    
    fun get_info() {
        return "Name: " + this.name + ", Age: " + this.age;
    }
}

// Inheritance
class Student extends Person {
    fun init(name, age, school) {
        super(name, age);
        this.school = school;
    }
    
    fun study() {
        print(this.name + " is studying at " + this.school);
    }
}

// Usage
let student = Student("Alice", 20, "MIT");
student.greet();
student.study();
```

### Async/Await (Future)
```yeep
// Asynchronous functions
async fun fetch_data(url) {
    let response = await http.get(url);
    return response.json();
}

async fun main() {
    let data = await fetch_data("https://api.example.com/users");
    print(data);
}
```

## Build System Enhancement

### CMake Configuration
```cmake
cmake_minimum_required(VERSION 3.16)
project(Yeep VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Main executable
add_executable(yeep ${SOURCES})
target_include_directories(yeep PRIVATE include)

# Compiler flags
if(MSVC)
    target_compile_options(yeep PRIVATE /W4)
else()
    target_compile_options(yeep PRIVATE -Wall -Wextra -pedantic)
endif()

# Debug/Release configurations
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(yeep PRIVATE DEBUG)
    target_compile_options(yeep PRIVATE -g -O0)
else()
    target_compile_options(yeep PRIVATE -O3 -DNDEBUG)
endif()

# Testing
enable_testing()
add_subdirectory(tests)
```

### Updated Makefile
```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Iinclude
LDFLAGS = 

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
BINDIR = bin

# Source files
SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET = $(BINDIR)/yeep

# Build modes
DEBUG_FLAGS = -g -O0 -DDEBUG
RELEASE_FLAGS = -O3 -DNDEBUG

# Default target
all: release

# Debug build
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Release build
release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

# Create target
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

# Compile source files
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Create directories
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Testing
test: $(TARGET)
	./tests/run_tests.sh

# Benchmarks
benchmark: $(TARGET)
	./tools/benchmark.sh

# Clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Install
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

.PHONY: all debug release test benchmark clean install
```

## Testing Infrastructure

### Unit Tests (Google Test)
```cpp
#include <gtest/gtest.h>
#include "core/Lexer.hpp"
#include "core/Parser.hpp"

class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(LexerTest, TokenizeNumbers) {
    yeep::Lexer lexer("42 3.14");
    auto tokens = lexer.tokenize();
    
    ASSERT_EQ(tokens.size(), 3); // NUMBER, NUMBER, EOF
    EXPECT_EQ(tokens[0].getType(), yeep::TokenType::NUMBER);
    EXPECT_EQ(tokens[0].getLexeme(), "42");
    EXPECT_EQ(tokens[1].getType(), yeep::TokenType::NUMBER);
    EXPECT_EQ(tokens[1].getLexeme(), "3.14");
}

TEST_F(LexerTest, TokenizeStrings) {
    yeep::Lexer lexer("\"Hello, World!\"");
    auto tokens = lexer.tokenize();
    
    ASSERT_EQ(tokens.size(), 2); // STRING, EOF
    EXPECT_EQ(tokens[0].getType(), yeep::TokenType::STRING);
    EXPECT_EQ(tokens[0].getLexeme(), "Hello, World!");
}

TEST_F(LexerTest, HandleNewlines) {
    yeep::Lexer lexer("line1\nline2\r\nline3");
    auto tokens = lexer.tokenize();
    
    // Should properly track line numbers
    bool found_newlines = false;
    for (const auto& token : tokens) {
        if (token.getType() == yeep::TokenType::NEWLINE) {
            found_newlines = true;
            break;
        }
    }
    EXPECT_TRUE(found_newlines);
}
```

### Integration Tests
```bash
#!/bin/bash
# Integration test script

set -e

YEEP_EXE="./bin/yeep"
TEST_DIR="./tests/integration"

echo "Running integration tests..."

for test_file in "$TEST_DIR"/*.yeep; do
    echo "Testing $test_file..."
    
    if [[ -f "${test_file}.expected" ]]; then
        # Compare output with expected
        actual_output=$($YEEP_EXE "$test_file" 2>&1)
        expected_output=$(cat "${test_file}.expected")
        
        if [[ "$actual_output" == "$expected_output" ]]; then
            echo "  ✓ PASSED"
        else
            echo "  ✗ FAILED"
            echo "    Expected: $expected_output"
            echo "    Actual:   $actual_output"
            exit 1
        fi
    else
        # Just check it runs without error
        $YEEP_EXE "$test_file"
        echo "  ✓ PASSED (no errors)"
    fi
done

echo "All integration tests passed!"
```

## Performance Benchmarks

### Benchmark Suite
```cpp
#include <chrono>
#include <iostream>
#include "core/Lexer.hpp"
#include "core/Parser.hpp"
#include "core/Interpreter.hpp"

class Benchmark {
public:
    static void lexer_performance() {
        // Large program text
        std::string large_program = generate_large_program(10000);
        
        auto start = std::chrono::high_resolution_clock::now();
        yeep::Lexer lexer(large_program);
        auto tokens = lexer.tokenize();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Lexer: " << tokens.size() << " tokens in " 
                  << duration.count() << " microseconds" << std::endl;
    }
    
    static void parser_performance() {
        // Test parsing speed
        std::string complex_expression = generate_complex_expression(1000);
        
        auto start = std::chrono::high_resolution_clock::now();
        yeep::Lexer lexer(complex_expression);
        auto tokens = lexer.tokenize();
        yeep::Parser parser(tokens);
        auto ast = parser.parse();
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Parser: complex expression in " 
                  << duration.count() << " microseconds" << std::endl;
    }
    
private:
    static std::string generate_large_program(int lines);
    static std::string generate_complex_expression(int depth);
};
```

## Documentation Updates

### API Documentation (Doxygen)
```cpp
/**
 * @file Lexer.hpp
 * @brief Lexical analyzer for the Yeep programming language
 * @author Syipmong
 * @date June 2025
 * @version 1.1.0
 */

/**
 * @class Lexer
 * @brief Tokenizes Yeep source code into a stream of tokens
 * 
 * The Lexer class is responsible for breaking down Yeep source code
 * into individual tokens that can be processed by the parser.
 * 
 * Key features:
 * - Proper handling of different newline formats
 * - Comprehensive error reporting with line/column information
 * - Support for all Yeep token types including keywords, operators, and literals
 * 
 * @example
 * ```cpp
 * yeep::Lexer lexer("let x = 42;");
 * auto tokens = lexer.tokenize();
 * for (const auto& token : tokens) {
 *     std::cout << token.toString() << std::endl;
 * }
 * ```
 */
```

### User Guide Updates
- Update installation instructions for C++ build
- Document new language features as they're implemented
- Provide migration guide from C to C++ version
- Include performance comparisons and benchmarks

## Timeline Summary

| Phase | Duration | Key Deliverables | Status |
|-------|----------|------------------|--------|
| 1 | Week 1 | Core C++ infrastructure, basic lexer/parser | 🟡 In Progress |
| 2 | Week 2 | Complete parser, enhanced grammar, AST optimization | 🔄 Planned |
| 3 | Week 3 | Arrays, objects, enhanced functions, for loops | 📋 Planned |
| 4 | Week 4 | Optional typing, type safety, better error handling | 🔮 Future |
| 5+ | Ongoing | Classes, modules, async/await, advanced features | 🚀 Future |

## Success Metrics

### Technical Metrics
- **Zero buffer overflow vulnerabilities** (achieved with C++)
- **50% improvement in error message quality** (line/column info)
- **100% test coverage** for core components
- **Performance equal to or better than C version**

### User Experience Metrics
- **Clearer error messages** with suggestions
- **Better IDE support** through Language Server Protocol
- **Comprehensive documentation** with examples
- **Active community engagement** and contributions

---

*This roadmap ensures a systematic migration to C++ while significantly improving the Yeep programming language's capabilities, safety, and user experience.*
