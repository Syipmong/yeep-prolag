# Grammar Validation and Testing Guide

## Overview
This document provides tools and guidelines for validating the Yeep grammar implementation and testing language features.

## Grammar Test Categories

### 1. Lexical Analysis Tests
Test that the lexer correctly identifies all token types:

```yeep
// Keywords
let fun if else while true false print return

// Operators
+ - * / = == != < > <= >=

// Delimiters
( ) { } ; ,

// Literals
42 3.14 "string" true false

// Identifiers
variable_name functionName _underscore
```

### 2. Syntax Analysis Tests
Test that the parser correctly builds AST for all grammar productions:

#### Variable Declarations
```yeep
let x = 5;
let name = "Alice";
let isActive = true;
```

#### Function Declarations
```yeep
fun simple() {
    print("Hello");
}

fun with_params(a, b, c) {
    return a + b + c;
}

fun recursive(n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * recursive(n - 1);
    }
}
```

#### Expressions
```yeep
// Arithmetic
2 + 3 * 4 - 1
(2 + 3) * (4 - 1)

// Comparison
x == y
a < b && c > d

// Function calls
add(1, 2)
nested_call(func1(a), func2(b))
```

#### Control Flow
```yeep
// If statements
if (condition) {
    statement;
}

if (condition) {
    statement1;
} else {
    statement2;
}

// While loops
while (counter < 10) {
    counter = counter + 1;
}
```

### 3. Semantic Analysis Tests
Test that the interpreter correctly handles language semantics:

#### Scope Resolution
```yeep
let global = "global";

fun test() {
    let local = "local";
    print(global); // Should work
    print(local);  // Should work
}

print(global); // Should work
// print(local); // Should error
```

#### Type Coercion
```yeep
let num = 42;
let str = "The answer is " + num; // Should convert num to string
print(str); // "The answer is 42"
```

#### Function Closures
```yeep
fun outer(x) {
    fun inner(y) {
        return x + y; // Should access x from outer scope
    }
    return inner;
}

let add5 = outer(5);
print(add5(3)); // Should print 8
```

## Automated Testing Tools

### Grammar Validator Script
```python
#!/usr/bin/env python3
"""
Grammar validation tool for Yeep programming language.
Tests various grammar productions and reports results.
"""

import subprocess
import os
import sys

class GrammarValidator:
    def __init__(self, yeep_executable):
        self.yeep_exe = yeep_executable
        self.test_cases = []
        self.results = []
    
    def add_test(self, name, code, expected_output=None, should_error=False):
        """Add a test case to the validation suite."""
        self.test_cases.append({
            'name': name,
            'code': code,
            'expected_output': expected_output,
            'should_error': should_error
        })
    
    def run_test(self, test_case):
        """Run a single test case."""
        # Write code to temporary file
        with open('temp_test.yeep', 'w') as f:
            f.write(test_case['code'])
        
        try:
            # Run Yeep interpreter
            result = subprocess.run(
                [self.yeep_exe, 'temp_test.yeep'],
                capture_output=True,
                text=True,
                timeout=10
            )
            
            success = True
            error_msg = None
            
            if test_case['should_error']:
                # Test should produce an error
                if result.returncode == 0:
                    success = False
                    error_msg = "Expected error but got success"
            else:
                # Test should succeed
                if result.returncode != 0:
                    success = False
                    error_msg = f"Unexpected error: {result.stderr}"
                elif test_case['expected_output']:
                    if test_case['expected_output'] not in result.stdout:
                        success = False
                        error_msg = f"Expected '{test_case['expected_output']}' in output"
            
            return {
                'success': success,
                'error_msg': error_msg,
                'stdout': result.stdout,
                'stderr': result.stderr,
                'returncode': result.returncode
            }
            
        except subprocess.TimeoutExpired:
            return {
                'success': False,
                'error_msg': 'Test timed out',
                'stdout': '',
                'stderr': '',
                'returncode': -1
            }
        finally:
            # Clean up
            if os.path.exists('temp_test.yeep'):
                os.remove('temp_test.yeep')
    
    def run_all_tests(self):
        """Run all test cases and generate report."""
        print("Running Yeep Grammar Validation Tests...")
        print("=" * 50)
        
        passed = 0
        total = len(self.test_cases)
        
        for i, test_case in enumerate(self.test_cases, 1):
            print(f"Test {i}/{total}: {test_case['name']}")
            
            result = self.run_test(test_case)
            
            if result['success']:
                print("  ✓ PASSED")
                passed += 1
            else:
                print(f"  ✗ FAILED: {result['error_msg']}")
                if result['stdout']:
                    print(f"    Output: {result['stdout'].strip()}")
                if result['stderr']:
                    print(f"    Error: {result['stderr'].strip()}")
            
            print()
        
        print("=" * 50)
        print(f"Results: {passed}/{total} tests passed")
        
        if passed == total:
            print("🎉 All tests passed!")
            return True
        else:
            print(f"❌ {total - passed} tests failed")
            return False

# Define test cases
def create_test_suite():
    validator = GrammarValidator('./yeep')
    
    # Basic literal tests
    validator.add_test(
        "Number literal",
        'print(42);',
        expected_output="42"
    )
    
    validator.add_test(
        "String literal",
        'print("Hello, World!");',
        expected_output="Hello, World!"
    )
    
    validator.add_test(
        "Boolean literal",
        'print(true);',
        expected_output="true"
    )
    
    # Variable declaration tests
    validator.add_test(
        "Variable declaration",
        '''
        let x = 10;
        print(x);
        ''',
        expected_output="10"
    )
    
    # Arithmetic tests
    validator.add_test(
        "Basic arithmetic",
        'print(2 + 3 * 4);',
        expected_output="14"
    )
    
    validator.add_test(
        "Parentheses precedence",
        'print((2 + 3) * 4);',
        expected_output="20"
    )
    
    # Function tests
    validator.add_test(
        "Function declaration and call",
        '''
        fun greet(name) {
            print("Hello, " + name + "!");
        }
        greet("Yeep");
        ''',
        expected_output="Hello, Yeep!"
    )
    
    validator.add_test(
        "Function with return value",
        '''
        fun add(a, b) {
            return a + b;
        }
        print(add(5, 3));
        ''',
        expected_output="8"
    )
    
    # Control flow tests
    validator.add_test(
        "If statement",
        '''
        let x = 10;
        if (x > 5) {
            print("Greater than 5");
        }
        ''',
        expected_output="Greater than 5"
    )
    
    validator.add_test(
        "If-else statement",
        '''
        let x = 3;
        if (x > 5) {
            print("Greater than 5");
        } else {
            print("Less than or equal to 5");
        }
        ''',
        expected_output="Less than or equal to 5"
    )
    
    validator.add_test(
        "While loop",
        '''
        let i = 1;
        while (i <= 3) {
            print(i);
            i = i + 1;
        }
        ''',
        expected_output="1"  # Just check for first output
    )
    
    # Error cases
    validator.add_test(
        "Undefined variable error",
        'print(undefined_variable);',
        should_error=True
    )
    
    validator.add_test(
        "Syntax error - missing semicolon",
        'let x = 5',
        should_error=True
    )
    
    return validator

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 grammar_validator.py <yeep_executable>")
        sys.exit(1)
    
    validator = create_test_suite()
    validator.yeep_exe = sys.argv[1]
    
    success = validator.run_all_tests()
    sys.exit(0 if success else 1)
```

### Test Runner Makefile
```makefile
# Grammar testing targets
.PHONY: test-grammar test-examples test-all

test-grammar:
	@echo "Running grammar validation tests..."
	python3 tools/grammar_validator.py ./yeep

test-examples:
	@echo "Testing example files..."
	@for file in examples/*.yeep; do \
		echo "Testing $$file..."; \
		./yeep "$$file" || exit 1; \
	done

test-all: test-grammar test-examples
	@echo "All tests completed successfully!"

grammar-benchmark:
	@echo "Running grammar performance benchmarks..."
	time ./yeep examples/grammar_test.yeep
	time ./yeep examples/fibonacci.yeep
	time ./yeep examples/control_flow.yeep
```

## Manual Testing Checklist

### Lexer Testing
- [ ] Keywords are recognized correctly
- [ ] Operators are tokenized properly
- [ ] String literals handle escape sequences
- [ ] Numbers (integers and floats) are parsed
- [ ] Comments are ignored
- [ ] Newlines are handled correctly
- [ ] Invalid characters produce appropriate errors

### Parser Testing
- [ ] Variable declarations parse correctly
- [ ] Function declarations parse correctly
- [ ] Expressions respect operator precedence
- [ ] Parentheses override precedence correctly
- [ ] Nested blocks parse properly
- [ ] Control flow statements parse correctly
- [ ] Function calls with various argument counts work
- [ ] Syntax errors are reported clearly

### Interpreter Testing
- [ ] Variables are stored and retrieved correctly
- [ ] Function calls work with proper parameter passing
- [ ] Scope rules are enforced correctly
- [ ] Return values are handled properly
- [ ] Control flow statements execute correctly
- [ ] Type coercion works as expected
- [ ] Error messages are helpful and accurate

### Edge Cases
- [ ] Empty programs
- [ ] Programs with only comments
- [ ] Deeply nested expressions
- [ ] Large numbers
- [ ] Very long strings
- [ ] Recursive functions
- [ ] Complex operator combinations

## Performance Testing

### Benchmark Programs
Create performance tests for:
1. **Large arithmetic expressions** - Test parser efficiency
2. **Deep recursion** - Test stack management
3. **Many variables** - Test symbol table performance
4. **Long-running loops** - Test interpreter efficiency

### Memory Testing
- Monitor memory usage during long-running programs
- Test for memory leaks in recursive functions
- Verify proper cleanup of temporary objects

## Regression Testing

### Automated Test Suite
Maintain a comprehensive suite of tests that run automatically:
1. All example programs should continue to work
2. Previously fixed bugs should not reoccur
3. Performance should not degrade significantly
4. Error messages should remain helpful

### Version Compatibility
- Test that old Yeep programs still work with new versions
- Document any breaking changes clearly
- Provide migration guides when necessary

---

*This validation framework ensures that the Yeep grammar implementation is correct, complete, and performant.*
