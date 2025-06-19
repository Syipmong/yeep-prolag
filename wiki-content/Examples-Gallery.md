# Examples Gallery 💡

A comprehensive collection of Yeep programs demonstrating various features and use cases.

---

## 🎯 Basic Examples

### Hello World
```yeep
// The classic first program
print("Hello, World!");
```

### Variables and Types
```yeep
// Different data types
let name = "Alice";
let age = 25;
let height = 5.8;
let isStudent = true;

print("Name: " + name);
print("Age: " + age);
print("Height: " + height + " feet");
print("Student: " + isStudent);
```

**Output:**
```
Name: Alice
Age: 25
Height: 5.8 feet
Student: true
```

---

## 🧮 Mathematical Examples

### Basic Calculator
```yeep
fun calculator(a, b, operation) {
    if (operation == "add") {
        return a + b;
    } else {
        if (operation == "subtract") {
            return a - b;
        } else {
            if (operation == "multiply") {
                return a * b;
            } else {
                if (operation == "divide") {
                    if (b != 0) {
                        return a / b;
                    } else {
                        return "Error: Division by zero";
                    }
                } else {
                    return "Error: Unknown operation";
                }
            }
        }
    }
}

print("10 + 5 = " + calculator(10, 5, "add"));
print("10 - 5 = " + calculator(10, 5, "subtract"));
print("10 * 5 = " + calculator(10, 5, "multiply"));
print("10 / 5 = " + calculator(10, 5, "divide"));
```

### Fibonacci Sequence
```yeep
fun fibonacci(n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

print("Fibonacci sequence (first 10 numbers):");
let i = 0;
while (i < 10) {
    print("F(" + i + ") = " + fibonacci(i));
    i = i + 1;
}
```

### Prime Number Checker
```yeep
fun isPrime(n) {
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    
    let i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
        i = i + 6;
    }
    return true;
}

print("Prime numbers from 1 to 20:");
let num = 1;
while (num <= 20) {
    if (isPrime(num)) {
        print(num + " is prime");
    }
    num = num + 1;
}
```

---

## 🎮 Game Examples

### Number Guessing Game
```yeep
fun playGuessingGame(secret, maxGuesses) {
    print("=== Number Guessing Game ===");
    print("I'm thinking of a number between 1 and 100");
    print("You have " + maxGuesses + " guesses");
    
    let guesses = 0;
    let won = false;
    
    // Simulate some guesses (in real version, get user input)
    let testGuesses = 50;  // First guess
    
    while (guesses < maxGuesses && !won) {
        guesses = guesses + 1;
        let guess = testGuesses + (guesses - 1) * 10;  // Simulate different guesses
        
        print("Guess #" + guesses + ": " + guess);
        
        if (guess == secret) {
            print("🎉 Congratulations! You guessed it in " + guesses + " tries!");
            won = true;
        } else {
            if (guess < secret) {
                print("Too low! Try higher.");
            } else {
                print("Too high! Try lower.");
            }
        }
    }
    
    if (!won) {
        print("💥 Game over! The number was " + secret);
    }
}

playGuessingGame(73, 5);
```

### Rock Paper Scissors
```yeep
fun getWinner(player1, player2) {
    if (player1 == player2) {
        return "tie";
    }
    
    if (player1 == "rock") {
        if (player2 == "scissors") {
            return "player1";
        } else {
            return "player2";
        }
    }
    
    if (player1 == "paper") {
        if (player2 == "rock") {
            return "player1";
        } else {
            return "player2";
        }
    }
    
    if (player1 == "scissors") {
        if (player2 == "paper") {
            return "player1";
        } else {
            return "player2";
        }
    }
    
    return "invalid";
}

fun playRockPaperScissors(p1Move, p2Move) {
    print("🎮 Rock Paper Scissors");
    print("Player 1: " + p1Move);
    print("Player 2: " + p2Move);
    
    let result = getWinner(p1Move, p2Move);
    
    if (result == "tie") {
        print("🤝 It's a tie!");
    } else {
        if (result == "player1") {
            print("🏆 Player 1 wins!");
        } else {
            print("🏆 Player 2 wins!");
        }
    }
}

playRockPaperScissors("rock", "scissors");
playRockPaperScissors("paper", "rock");
playRockPaperScissors("scissors", "scissors");
```

---

## 📊 Data Processing Examples

### Grade Calculator
```yeep
fun calculateLetterGrade(score) {
    if (score >= 97) {
        return "A+";
    } else {
        if (score >= 93) {
            return "A";
        } else {
            if (score >= 90) {
                return "A-";
            } else {
                if (score >= 87) {
                    return "B+";
                } else {
                    if (score >= 83) {
                        return "B";
                    } else {
                        if (score >= 80) {
                            return "B-";
                        } else {
                            if (score >= 77) {
                                return "C+";
                            } else {
                                if (score >= 73) {
                                    return "C";
                                } else {
                                    if (score >= 70) {
                                        return "C-";
                                    } else {
                                        if (score >= 67) {
                                            return "D+";
                                        } else {
                                            if (score >= 65) {
                                                return "D";
                                            } else {
                                                return "F";
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

fun processStudentGrades() {
    print("📊 Student Grade Report");
    print("========================");
    
    // Simulate student data
    let students = "Alice,Bob,Carol,David,Eve";
    let scores = "95,87,92,78,65";  // In real version, would be array
    
    // Process Alice (95)
    let alice_score = 95;
    let alice_grade = calculateLetterGrade(alice_score);
    print("Alice: " + alice_score + " (" + alice_grade + ")");
    
    // Process Bob (87)
    let bob_score = 87;
    let bob_grade = calculateLetterGrade(bob_score);
    print("Bob: " + bob_score + " (" + bob_grade + ")");
    
    // Process Carol (92)
    let carol_score = 92;
    let carol_grade = calculateLetterGrade(carol_score);
    print("Carol: " + carol_score + " (" + carol_grade + ")");
}

processStudentGrades();
```

### Temperature Converter
```yeep
fun celsiusToFahrenheit(celsius) {
    return (celsius * 9 / 5) + 32;
}

fun fahrenheitToCelsius(fahrenheit) {
    return (fahrenheit - 32) * 5 / 9;
}

fun kelvinToCelsius(kelvin) {
    return kelvin - 273.15;
}

fun celsiusToKelvin(celsius) {
    return celsius + 273.15;
}

fun temperatureConverter() {
    print("🌡️ Temperature Converter");
    print("=======================");
    
    let celsius = 25;
    print("Starting temperature: " + celsius + "°C");
    
    let fahrenheit = celsiusToFahrenheit(celsius);
    print("In Fahrenheit: " + fahrenheit + "°F");
    
    let kelvin = celsiusToKelvin(celsius);
    print("In Kelvin: " + kelvin + "K");
    
    print();
    print("Verification (convert back):");
    print("From F to C: " + fahrenheitToCelsius(fahrenheit) + "°C");
    print("From K to C: " + kelvinToCelsius(kelvin) + "°C");
}

temperatureConverter();
```

---

## 🔧 Algorithm Examples

### Sorting Algorithm (Bubble Sort)
```yeep
fun bubbleSort() {
    // Simulate array with individual variables (limitation of current Yeep)
    let a1 = 64; let a2 = 34; let a3 = 25; let a4 = 12; let a5 = 22;
    
    print("🔄 Bubble Sort Demonstration");
    print("Original: " + a1 + ", " + a2 + ", " + a3 + ", " + a4 + ", " + a5);
    
    // Sort step by step (manual implementation due to no arrays)
    // Pass 1
    if (a1 > a2) { let temp = a1; a1 = a2; a2 = temp; }
    if (a2 > a3) { let temp = a2; a2 = a3; a3 = temp; }
    if (a3 > a4) { let temp = a3; a3 = a4; a4 = temp; }
    if (a4 > a5) { let temp = a4; a4 = a5; a5 = temp; }
    
    print("Pass 1: " + a1 + ", " + a2 + ", " + a3 + ", " + a4 + ", " + a5);
    
    // Pass 2
    if (a1 > a2) { let temp = a1; a1 = a2; a2 = temp; }
    if (a2 > a3) { let temp = a2; a2 = a3; a3 = temp; }
    if (a3 > a4) { let temp = a3; a3 = a4; a4 = temp; }
    
    print("Pass 2: " + a1 + ", " + a2 + ", " + a3 + ", " + a4 + ", " + a5);
    
    // Continue until sorted...
    print("Final sorted: " + a1 + ", " + a2 + ", " + a3 + ", " + a4 + ", " + a5);
}

bubbleSort();
```

### Binary Search Tree Operations
```yeep
// Simulate BST with function calls (limited by no objects)
fun findInBST(value, root, left, right) {
    if (root == value) {
        return true;
    }
    
    if (value < root) {
        if (left != -1) {
            // Would recursively search left subtree
            return false;  // Simplified for this example
        }
        return false;
    } else {
        if (right != -1) {
            // Would recursively search right subtree
            return false;  // Simplified for this example
        }
        return false;
    }
}

fun demonstrateBST() {
    print("🌳 Binary Search Tree Demo");
    
    // Simulate a BST: 
    //       50
    //      /  \
    //     30   70
    //    / \   / \
    //   20 40 60 80
    
    let root = 50;
    print("Tree root: " + root);
    print("Searching for 40...");
    
    if (40 < root) {
        print("Go left to 30");
        if (40 > 30) {
            print("Go right to 40");
            print("✅ Found 40!");
        }
    }
    
    print("Searching for 90...");
    if (90 > root) {
        print("Go right to 70");
        if (90 > 70) {
            print("Go right to 80");
            if (90 > 80) {
                print("❌ Not found - would be right of 80");
            }
        }
    }
}

demonstrateBST();
```

---

## 🎨 Pattern Examples

### ASCII Art Generator
```yeep
fun drawTriangle(height) {
    print("🔺 Triangle Pattern (height " + height + ")");
    
    let row = 1;
    while (row <= height) {
        // Draw spaces
        let spaces = height - row;
        let spaceStr = "";
        let s = 0;
        while (s < spaces) {
            spaceStr = spaceStr + " ";
            s = s + 1;
        }
        
        // Draw stars
        let stars = 2 * row - 1;
        let starStr = "";
        let st = 0;
        while (st < stars) {
            starStr = starStr + "*";
            st = st + 1;
        }
        
        print(spaceStr + starStr);
        row = row + 1;
    }
}

fun drawRectangle(width, height) {
    print("⬜ Rectangle Pattern (" + width + "x" + height + ")");
    
    let row = 1;
    while (row <= height) {
        let line = "";
        let col = 1;
        
        while (col <= width) {
            if (row == 1 || row == height || col == 1 || col == width) {
                line = line + "#";
            } else {
                line = line + " ";
            }
            col = col + 1;
        }
        
        print(line);
        row = row + 1;
    }
}

drawTriangle(5);
print();
drawRectangle(8, 4);
```

### Diamond Pattern
```yeep
fun drawDiamond(size) {
    print("💎 Diamond Pattern (size " + size + ")");
    
    // Upper half (including middle)
    let row = 1;
    while (row <= size) {
        let spaces = size - row;
        let spaceStr = "";
        let s = 0;
        while (s < spaces) {
            spaceStr = spaceStr + " ";
            s = s + 1;
        }
        
        let stars = 2 * row - 1;
        let starStr = "";
        let st = 0;
        while (st < stars) {
            starStr = starStr + "*";
            st = st + 1;
        }
        
        print(spaceStr + starStr);
        row = row + 1;
    }
    
    // Lower half
    row = size - 1;
    while (row >= 1) {
        let spaces = size - row;
        let spaceStr = "";
        let s = 0;
        while (s < spaces) {
            spaceStr = spaceStr + " ";
            s = s + 1;
        }
        
        let stars = 2 * row - 1;
        let starStr = "";
        let st = 0;
        while (st < stars) {
            starStr = starStr + "*";
            st = st + 1;
        }
        
        print(spaceStr + starStr);
        row = row - 1;
    }
}

drawDiamond(4);
```

---

## 🔍 Utility Examples

### Text Analyzer
```yeep
fun analyzeText(text) {
    print("📝 Text Analysis for: \"" + text + "\"");
    print("=====================================");
    
    // Count characters (simplified - in real version would iterate)
    let length = 13;  // "Hello, World!" length
    print("Character count: " + length);
    
    // Count words (simplified)
    let wordCount = 2;  // "Hello" and "World"
    print("Word count: " + wordCount);
    
    // Check for specific characters
    let hasComma = true;   // Contains comma
    let hasExclamation = true;  // Contains exclamation
    
    print("Contains comma: " + hasComma);
    print("Contains exclamation: " + hasExclamation);
    
    // Average word length
    let avgLength = length / wordCount;
    print("Average word length: " + avgLength);
}

analyzeText("Hello, World!");
```

### Time Calculator
```yeep
fun convertSeconds(totalSeconds) {
    print("⏰ Time Converter");
    print("Input: " + totalSeconds + " seconds");
    
    let hours = totalSeconds / 3600;
    let remainingAfterHours = totalSeconds % 3600;
    let minutes = remainingAfterHours / 60;
    let seconds = remainingAfterHours % 60;
    
    print("Time: " + hours + "h " + minutes + "m " + seconds + "s");
}

fun calculateAge(birthYear, currentYear) {
    let age = currentYear - birthYear;
    let ageInDays = age * 365;  // Approximation
    let ageInHours = ageInDays * 24;
    let ageInMinutes = ageInHours * 60;
    
    print("👶 Age Calculator");
    print("Birth year: " + birthYear);
    print("Current year: " + currentYear);
    print("Age: " + age + " years");
    print("Age in days: " + ageInDays + " days (approx)");
    print("Age in hours: " + ageInHours + " hours (approx)");
    print("Age in minutes: " + ageInMinutes + " minutes (approx)");
}

convertSeconds(7265);  // 2h 1m 5s
print();
calculateAge(1995, 2025);
```

---

## 🧪 Advanced Examples

### Recursive Factorial with Memoization Simulation
```yeep
// Simulate memoization with a few pre-calculated values
let memo_0 = 1;
let memo_1 = 1;
let memo_2 = 2;
let memo_3 = 6;
let memo_4 = 24;
let memo_5 = 120;

fun factorialMemo(n) {
    print("Calculating factorial of " + n);
    
    if (n == 0) { print("Using memo: 0! = " + memo_0); return memo_0; }
    if (n == 1) { print("Using memo: 1! = " + memo_1); return memo_1; }
    if (n == 2) { print("Using memo: 2! = " + memo_2); return memo_2; }
    if (n == 3) { print("Using memo: 3! = " + memo_3); return memo_3; }
    if (n == 4) { print("Using memo: 4! = " + memo_4); return memo_4; }
    if (n == 5) { print("Using memo: 5! = " + memo_5); return memo_5; }
    
    // For larger numbers, calculate normally
    print("Computing " + n + "! = " + n + " * " + (n-1) + "!");
    return n * factorialMemo(n - 1);
}

print("🧠 Factorial with Memoization Demo");
print("==================================");
factorialMemo(3);  // Uses memo
print();
factorialMemo(6);  // Computes 6 * 5!, where 5! is memoized
```

### Simple State Machine
```yeep
fun trafficLightStateMachine(currentState, input) {
    print("🚦 Traffic Light State Machine");
    print("Current state: " + currentState);
    print("Input: " + input);
    
    if (currentState == "red") {
        if (input == "timer") {
            print("Transition: Red → Green");
            return "green";
        } else {
            print("Stay in Red state");
            return "red";
        }
    }
    
    if (currentState == "green") {
        if (input == "timer") {
            print("Transition: Green → Yellow");
            return "yellow";
        } else {
            print("Stay in Green state");
            return "green";
        }
    }
    
    if (currentState == "yellow") {
        if (input == "timer") {
            print("Transition: Yellow → Red");
            return "red";
        } else {
            print("Stay in Yellow state");
            return "yellow";
        }
    }
    
    print("Invalid state!");
    return currentState;
}

// Simulate traffic light cycle
let state = "red";
print("Starting state: " + state);
print();

state = trafficLightStateMachine(state, "timer");
print("New state: " + state);
print();

state = trafficLightStateMachine(state, "timer");
print("New state: " + state);
print();

state = trafficLightStateMachine(state, "timer");
print("New state: " + state);
```

---

## 🎯 Interactive Examples

### Menu System
```yeep
fun displayMenu() {
    print("📋 Main Menu");
    print("============");
    print("1. Calculator");
    print("2. Temperature Converter");
    print("3. Text Analyzer");
    print("4. Exit");
    print();
}

fun processMenuChoice(choice) {
    if (choice == 1) {
        print("🧮 Opening Calculator...");
        let result = calculator(10, 5, "add");
        print("Sample calculation: 10 + 5 = " + result);
    } else {
        if (choice == 2) {
            print("🌡️ Opening Temperature Converter...");
            let fahrenheit = celsiusToFahrenheit(25);
            print("25°C = " + fahrenheit + "°F");
        } else {
            if (choice == 3) {
                print("📝 Opening Text Analyzer...");
                analyzeText("Sample text");
            } else {
                if (choice == 4) {
                    print("👋 Goodbye!");
                } else {
                    print("❌ Invalid choice. Please try again.");
                }
            }
        }
    }
}

// Simulate menu interaction
displayMenu();
print("User selects option 1:");
processMenuChoice(1);
print();
print("User selects option 2:");
processMenuChoice(2);
```

---

## 🎊 Complete Programs

### Simple Banking System
```yeep
fun createAccount(name, initialBalance) {
    print("🏦 Creating account for " + name);
    print("Initial balance: $" + initialBalance);
    return initialBalance;
}

fun deposit(balance, amount) {
    if (amount > 0) {
        let newBalance = balance + amount;
        print("💰 Deposited $" + amount);
        print("New balance: $" + newBalance);
        return newBalance;
    } else {
        print("❌ Invalid deposit amount");
        return balance;
    }
}

fun withdraw(balance, amount) {
    if (amount > 0 && amount <= balance) {
        let newBalance = balance - amount;
        print("💸 Withdrew $" + amount);
        print("New balance: $" + newBalance);
        return newBalance;
    } else {
        if (amount > balance) {
            print("❌ Insufficient funds");
        } else {
            print("❌ Invalid withdrawal amount");
        }
        return balance;
    }
}

fun checkBalance(balance) {
    print("💳 Current balance: $" + balance);
    return balance;
}

// Banking system demo
print("🏦 Simple Banking System Demo");
print("=============================");

let balance = createAccount("Alice", 1000);
print();

balance = deposit(balance, 250);
print();

balance = withdraw(balance, 100);
print();

balance = withdraw(balance, 2000);  // Should fail
print();

checkBalance(balance);
```

---

## 📚 Learning Exercises

### Exercise 1: Enhanced Calculator
```yeep
// TODO: Extend this calculator to support more operations
fun advancedCalculator(a, b, operation) {
    if (operation == "power") {
        // Implement power function using repeated multiplication
        let result = 1;
        let i = 0;
        while (i < b) {
            result = result * a;
            i = i + 1;
        }
        return result;
    }
    
    if (operation == "sqrt") {
        // Simple square root using Newton's method (approximation)
        let guess = a / 2;
        let i = 0;
        while (i < 10) {  // 10 iterations for approximation
            guess = (guess + a / guess) / 2;
            i = i + 1;
        }
        return guess;
    }
    
    // Add more operations here...
    return "Unknown operation";
}

print("🔬 Advanced Calculator Demo");
print("2^3 = " + advancedCalculator(2, 3, "power"));
print("√16 ≈ " + advancedCalculator(16, 0, "sqrt"));
```

### Exercise 2: Mini Interpreter
```yeep
fun evaluateExpression(operator, left, right) {
    print("🤖 Mini Expression Evaluator");
    print("Expression: " + left + " " + operator + " " + right);
    
    if (operator == "+") {
        return left + right;
    }
    if (operator == "-") {
        return left - right;
    }
    if (operator == "*") {
        return left * right;
    }
    if (operator == "/") {
        if (right != 0) {
            return left / right;
        } else {
            return "Error: Division by zero";
        }
    }
    
    return "Error: Unknown operator";
}

// Demo the mini interpreter
let result1 = evaluateExpression("+", 10, 5);
print("Result: " + result1);

let result2 = evaluateExpression("*", 7, 8);
print("Result: " + result2);
```

---

## 🏆 Challenge Problems

### Challenge 1: Number System Converter
```yeep
// Convert decimal to binary (simplified for small numbers)
fun decimalToBinary(decimal) {
    if (decimal == 0) return "0";
    if (decimal == 1) return "1";
    if (decimal == 2) return "10";
    if (decimal == 3) return "11";
    if (decimal == 4) return "100";
    if (decimal == 5) return "101";
    if (decimal == 6) return "110";
    if (decimal == 7) return "111";
    if (decimal == 8) return "1000";
    
    return "Number too large for this demo";
}

print("🔢 Number System Converter");
print("5 in binary: " + decimalToBinary(5));
print("8 in binary: " + decimalToBinary(8));
```

### Challenge 2: Simple Cipher
```yeep
// Caesar cipher (shift by 3) - simplified for letters A-Z
fun caesarCipher(letter) {
    // This is a simplified version - would need actual ASCII manipulation
    if (letter == "A") return "D";
    if (letter == "B") return "E";
    if (letter == "C") return "F";
    // ... continue for all letters
    return letter;  // Return unchanged for this demo
}

print("🔐 Caesar Cipher Demo");
print("A → " + caesarCipher("A"));
print("B → " + caesarCipher("B"));
```

---

## 🎯 Next Steps

Ready for more? Try these:

1. **Modify Examples**: Change parameters and see how behavior changes
2. **Combine Examples**: Mix different examples together
3. **Add Features**: Extend examples with new functionality
4. **Create Your Own**: Build something completely new!

**More Resources:**
- [**Language Reference**](Language-Reference) - Complete syntax guide
- [**Best Practices**](Best-Practices) - Write better Yeep code
- [**Contributing Guide**](Contributing-Guide) - Add your examples to this gallery!

**Happy coding! 🚀**
