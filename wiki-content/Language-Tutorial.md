# Yeep Language Tutorial 📚

Welcome to Yeep! This tutorial will teach you everything you need to know to start programming in Yeep.

---

## 🎯 Getting Started

### Your First Yeep Program

Let's start with the classic "Hello, World!":

```yeep
print("Hello, World!");
```

Save this as `hello.yeep` and run:
```bash
yeep hello.yeep
```

**Output:**
```
Hello, World!
```

---

## 📊 Variables and Data Types

### Declaring Variables
Yeep uses `let` to declare variables:

```yeep
let name = "Alice";
let age = 25;
let isStudent = true;
let height = 5.8;
```

### Data Types
Yeep supports three main data types:

#### 🔢 Numbers
```yeep
let integer = 42;
let decimal = 3.14159;
let negative = -10;

print(integer + decimal);  // 45.14159
```

#### 📝 Strings
```yeep
let greeting = "Hello";
let target = "World";
let message = greeting + ", " + target + "!";

print(message);  // Hello, World!
```

#### ✅ Booleans
```yeep
let isTrue = true;
let isFalse = false;

print(isTrue);   // true
print(isFalse);  // false
```

---

## 🧮 Expressions and Operators

### Arithmetic Operators
```yeep
let a = 10;
let b = 3;

print(a + b);  // 13 (addition)
print(a - b);  // 7  (subtraction)
print(a * b);  // 30 (multiplication)
print(a / b);  // 3  (division)
print(a % b);  // 1  (modulo)
```

### Comparison Operators
```yeep
let x = 5;
let y = 10;

print(x == y);  // false (equal)
print(x != y);  // true  (not equal)
print(x < y);   // true  (less than)
print(x > y);   // false (greater than)
print(x <= y);  // true  (less than or equal)
print(x >= y);  // false (greater than or equal)
```

### Logical Operators
```yeep
let a = true;
let b = false;

print(a && b);  // false (AND)
print(a || b);  // true  (OR)
print(!a);      // false (NOT)
print(!b);      // true  (NOT)
```

#### Short-Circuit Evaluation
```yeep
// && stops at first false value
print(false && "not evaluated");  // false

// || stops at first true value  
print(true || "not evaluated");   // true
```

---

## 🔗 String Concatenation

Yeep can concatenate strings with any data type:

```yeep
let name = "Alice";
let age = 25;
let isStudent = true;

print("Name: " + name);          // Name: Alice
print("Age: " + age);            // Age: 25
print("Student: " + isStudent);  // Student: true

// Complex concatenation
let info = "User " + name + " is " + age + " years old";
print(info);  // User Alice is 25 years old
```

---

## 🔀 Control Flow

### If-Else Statements

#### Basic If
```yeep
let score = 85;

if (score >= 90) {
    print("Grade: A");
}
```

#### If-Else
```yeep
let temperature = 22;

if (temperature > 25) {
    print("It's hot!");
} else {
    print("It's not hot.");
}
```

#### Nested If-Else
```yeep
let score = 85;

if (score >= 90) {
    print("Grade: A");
} else {
    if (score >= 80) {
        print("Grade: B");
    } else {
        if (score >= 70) {
            print("Grade: C");
        } else {
            print("Grade: F");
        }
    }
}
```

### While Loops

#### Basic While Loop
```yeep
let count = 1;

while (count <= 5) {
    print("Count: " + count);
    count = count + 1;
}
```

**Output:**
```
Count: 1
Count: 2
Count: 3
Count: 4
Count: 5
```

#### While with Conditions
```yeep
let number = 16;

while (number > 1) {
    print("Number: " + number);
    number = number / 2;
}
```

**Output:**
```
Number: 16
Number: 8
Number: 4
Number: 2
```

---

## 🎯 Functions

### Defining Functions
```yeep
fun greet(name) {
    print("Hello, " + name + "!");
}

// Call the function
greet("Alice");  // Hello, Alice!
greet("Bob");    // Hello, Bob!
```

### Functions with Return Values
```yeep
fun add(a, b) {
    return a + b;
}

let result = add(5, 3);
print("5 + 3 = " + result);  // 5 + 3 = 8
```

### Multiple Parameters
```yeep
fun introduce(name, age, city) {
    return "Hi, I'm " + name + ", " + age + " years old, from " + city;
}

let intro = introduce("Alice", 25, "New York");
print(intro);  // Hi, I'm Alice, 25 years old, from New York
```

### Recursive Functions
```yeep
fun factorial(n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

print("5! = " + factorial(5));  // 5! = 120
```

---

## 🧩 Practical Examples

### Example 1: Number Guessing Game
```yeep
fun guessNumber() {
    let secret = 7;  // In real version, this would be random
    let guess = 5;   // In real version, this would be user input
    
    if (guess == secret) {
        print("Congratulations! You guessed correctly!");
    } else {
        if (guess < secret) {
            print("Too low! The number was " + secret);
        } else {
            print("Too high! The number was " + secret);
        }
    }
}

guessNumber();
```

### Example 2: Fibonacci Sequence
```yeep
fun fibonacci(n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

print("Fibonacci sequence:");
let i = 0;
while (i < 10) {
    print("F(" + i + ") = " + fibonacci(i));
    i = i + 1;
}
```

### Example 3: Grade Calculator
```yeep
fun calculateGrade(score) {
    if (score >= 90) {
        return "A";
    } else {
        if (score >= 80) {
            return "B";
        } else {
            if (score >= 70) {
                return "C";
            } else {
                if (score >= 60) {
                    return "D";
                } else {
                    return "F";
                }
            }
        }
    }
}

fun displayGrade(name, score) {
    let grade = calculateGrade(score);
    print(name + " scored " + score + " and got grade " + grade);
}

displayGrade("Alice", 95);  // Alice scored 95 and got grade A
displayGrade("Bob", 72);    // Bob scored 72 and got grade C
displayGrade("Carol", 58);  // Carol scored 58 and got grade F
```

---

## 💬 Interactive Mode (REPL)

Start the interactive shell to experiment:

```bash
$ yeep
Yeep Programming Language v1.0.8
Type 'exit' to quit, 'help' for help.

yeep> let x = 42;
yeep> print("The answer is " + x);
The answer is 42
yeep> fun double(n) { return n * 2; }
yeep> print(double(21));
42
yeep> exit
```

---

## 🎪 Advanced Features

### Shebang Scripts (Linux/macOS)
Create executable scripts:

```yeep
#!/usr/bin/env yeep

print("This is an executable Yeep script!");
let name = "Yeep";
print("Welcome to " + name + "!");
```

Make it executable:
```bash
chmod +x script.yeep
./script.yeep
```

### Command Line Arguments
```bash
# Show version
yeep --version

# Show help
yeep --help

# Run script
yeep script.yeep
```

---

## 🏆 Best Practices

1. **Use meaningful variable names**:
   ```yeep
   // Good
   let userName = "Alice";
   let accountBalance = 1000.50;
   
   // Avoid
   let x = "Alice";
   let b = 1000.50;
   ```

2. **Keep functions small and focused**:
   ```yeep
   // Good
   fun calculateTax(income) {
       return income * 0.15;
   }
   
   fun calculateNetIncome(income) {
       let tax = calculateTax(income);
       return income - tax;
   }
   ```

3. **Use comments for complex logic**:
   ```yeep
   // Calculate compound interest
   fun compoundInterest(principal, rate, time) {
       // A = P(1 + r/n)^(nt), assuming n=1 (annually)
       return principal * (1 + rate) * time;
   }
   ```

---

## 🎯 Next Steps

Congratulations! You now know the basics of Yeep. Here's what to explore next:

- 📖 [**Language Reference**](Language-Reference) - Complete syntax documentation
- 💡 [**Examples Gallery**](Examples-Gallery) - More complex examples
- 🎯 [**Best Practices**](Best-Practices) - Writing better Yeep code
- ❓ [**FAQ**](FAQ) - Common questions and answers

**Happy coding with Yeep! 🚀**
