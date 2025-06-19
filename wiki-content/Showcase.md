# Showcase

This page highlights interesting projects, examples, and use cases built with the Yeep programming language.

## Featured Projects

### Calculator Applications

#### Basic Calculator
A simple calculator demonstrating arithmetic operations.

**File: `calculator.yeep`**
```yeep
# Simple Calculator Example
print "=== Yeep Calculator ==="
print ""

# Basic arithmetic operations
a = 15
b = 3

print "Numbers: a = " + a + ", b = " + b
print ""

# Addition
sum = a + b
print "Addition: " + a + " + " + b + " = " + sum

# Subtraction  
difference = a - b
print "Subtraction: " + a + " - " + b + " = " + difference

# Multiplication
product = a * b
print "Multiplication: " + a + " * " + b + " = " + product

# Division
quotient = a / b
print "Division: " + a + " / " + b + " = " + quotient

# Modulo
remainder = a % b
print "Modulo: " + a + " % " + b + " = " + remainder

print ""
print "Calculator complete!"
```

**Output:**
```
=== Yeep Calculator ===

Numbers: a = 15, b = 3

Addition: 15 + 3 = 18
Subtraction: 15 - 3 = 12
Multiplication: 15 * 3 = 45
Division: 15 / 3 = 5
Modulo: 15 % 3 = 0

Calculator complete!
```

### Logic Demonstrations

#### Boolean Logic Explorer
Demonstrates logical operations and truth tables.

**File: `logic_explorer.yeep`**
```yeep
# Boolean Logic Explorer
print "=== Boolean Logic in Yeep ==="
print ""

# Basic boolean values
true_val = true
false_val = false

print "Basic Values:"
print "true_val = " + true_val
print "false_val = " + false_val
print ""

# AND operations
print "AND Operations:"
print "true and true = " + (true_val and true_val)
print "true and false = " + (true_val and false_val)
print "false and true = " + (false_val and true_val)
print "false and false = " + (false_val and false_val)
print ""

# OR operations
print "OR Operations:"
print "true or true = " + (true_val or true_val)
print "true or false = " + (true_val or false_val)
print "false or true = " + (false_val or true_val)
print "false or false = " + (false_val or false_val)
print ""

# NOT operations
print "NOT Operations:"
print "not true = " + (not true_val)
print "not false = " + (not false_val)
print ""

# Complex expressions
age = 25
has_license = true
is_student = false

can_drive = age >= 18 and has_license
gets_discount = is_student or age >= 65

print "Real-world Logic:"
print "Age: " + age
print "Has License: " + has_license
print "Is Student: " + is_student
print ""
print "Can Drive: " + can_drive
print "Gets Discount: " + gets_discount
```

### Educational Examples

#### Number Pattern Generator
Creates interesting number patterns and sequences.

**File: `patterns.yeep`**
```yeep
# Number Pattern Generator
print "=== Number Patterns in Yeep ==="
print ""

# Fibonacci-like sequence (first few terms)
print "Fibonacci-like Sequence:"
a = 0
b = 1
print "Term 1: " + a
print "Term 2: " + b

c = a + b
print "Term 3: " + c

d = b + c
print "Term 4: " + d

e = c + d
print "Term 5: " + e
print ""

# Powers of 2
print "Powers of 2:"
power = 1
print "2^0 = " + power

power = power * 2
print "2^1 = " + power

power = power * 2
print "2^2 = " + power

power = power * 2
print "2^3 = " + power

power = power * 2
print "2^4 = " + power
print ""

# Mathematical relationships
print "Mathematical Relationships:"
x = 5
square = x * x
cube = square * x

print "x = " + x
print "x² = " + square
print "x³ = " + cube
print "x² + x³ = " + (square + cube)
```

### Text Processing

#### String Manipulation Demo
Shows string operations and text processing.

**File: `text_processor.yeep`**
```yeep
# String Manipulation Demo
print "=== Text Processing in Yeep ==="
print ""

# Basic string operations
first_name = "Alice"
last_name = "Johnson"
full_name = first_name + " " + last_name

print "Name Processing:"
print "First Name: " + first_name
print "Last Name: " + last_name
print "Full Name: " + full_name
print ""

# Building messages
greeting = "Hello, " + first_name + "!"
farewell = "Goodbye, " + full_name + ". Have a great day!"

print "Messages:"
print greeting
print farewell
print ""

# Data formatting
product = "Laptop"
price = 999
quantity = 2
total = price * quantity

report = "Product: " + product + ", Price: $" + price + ", Quantity: " + quantity + ", Total: $" + total

print "Sales Report:"
print report
print ""

# Template-like string building
template_start = "Dear "
template_middle = ", welcome to our service! Your account ID is "
template_end = ". Please keep this information safe."

user_name = "Bob"
account_id = 12345
welcome_message = template_start + user_name + template_middle + account_id + template_end

print "Welcome Message:"
print welcome_message
```

## Community Contributions

### Educational Utilities

#### Grade Calculator
Calculates final grades based on different components.

**Contributed by: Community Member**
```yeep
# Grade Calculator
print "=== Grade Calculator ==="
print ""

# Grade components
homework_score = 85
midterm_score = 78
final_score = 92
participation = 95

# Weights (as percentages)
homework_weight = 30
midterm_weight = 25
final_weight = 35
participation_weight = 10

# Calculate weighted scores
homework_points = homework_score * homework_weight / 100
midterm_points = midterm_score * midterm_weight / 100
final_points = final_score * final_weight / 100
participation_points = participation * participation_weight / 100

# Final grade
final_grade = homework_points + midterm_points + final_points + participation_points

print "Grade Breakdown:"
print "Homework (" + homework_weight + "%): " + homework_score + " → " + homework_points + " points"
print "Midterm (" + midterm_weight + "%): " + midterm_score + " → " + midterm_points + " points"
print "Final (" + final_weight + "%): " + final_score + " → " + final_points + " points"
print "Participation (" + participation_weight + "%): " + participation + " → " + participation_points + " points"
print ""
print "Final Grade: " + final_grade + "%"

# Letter grade assignment
letter_grade = "F"
if final_grade >= 90 {
    letter_grade = "A"
} else if final_grade >= 80 {
    letter_grade = "B"
} else if final_grade >= 70 {
    letter_grade = "C"
} else if final_grade >= 60 {
    letter_grade = "D"
}

print "Letter Grade: " + letter_grade
```

### Business Applications

#### Simple Inventory Tracker
Basic inventory management system.

**Contributed by: Business User**
```yeep
# Simple Inventory Tracker
print "=== Inventory Management ==="
print ""

# Product information
product_name = "Widget A"
initial_stock = 100
units_sold = 23
units_received = 50
reorder_point = 30

# Calculate current stock
current_stock = initial_stock - units_sold + units_received

# Stock status
needs_reorder = current_stock <= reorder_point

print "Product: " + product_name
print "Initial Stock: " + initial_stock
print "Units Sold: " + units_sold
print "Units Received: " + units_received
print "Current Stock: " + current_stock
print "Reorder Point: " + reorder_point
print "Needs Reorder: " + needs_reorder

if needs_reorder {
    suggested_order = reorder_point * 3 - current_stock
    print "Suggested Order Quantity: " + suggested_order
}
```

## Creative Applications

### Art and Design

#### ASCII Pattern Generator
Creates simple ASCII art patterns.

```yeep
# ASCII Pattern Generator
print "=== ASCII Art Patterns ==="
print ""

# Simple patterns using repeated characters
print "Pattern 1 - Stars:"
line1 = "*"
line2 = "**"
line3 = "***"
line4 = "****"
line5 = "*****"

print line1
print line2
print line3
print line4
print line5
print line4
print line3
print line2
print line1
print ""

# Number patterns
print "Pattern 2 - Numbers:"
row1 = "1"
row2 = "12"
row3 = "123"
row4 = "1234"
row5 = "12345"

print row1
print row2
print row3
print row4
print row5
```

### Games and Puzzles

#### Number Guessing Game Setup
Prepares a simple number guessing game.

```yeep
# Number Guessing Game Setup
print "=== Number Guessing Game ==="
print ""

# Game configuration
secret_number = 42
max_attempts = 5
current_attempt = 1

print "Welcome to the Number Guessing Game!"
print "I'm thinking of a number between 1 and 100."
print "You have " + max_attempts + " attempts to guess it."
print ""

# Simulated guesses (in future version, this would be interactive)
guess1 = 25
guess2 = 60
guess3 = 45
guess4 = 40
guess5 = 42

print "Attempt " + current_attempt + ": Guess = " + guess1
result1 = guess1 == secret_number
print "Correct: " + result1
if not result1 {
    hint1 = guess1 < secret_number
    if hint1 {
        print "Hint: Too low!"
    } else {
        print "Hint: Too high!"
    }
}
print ""

# Continue with more attempts...
current_attempt = current_attempt + 1
print "Attempt " + current_attempt + ": Guess = " + guess2
# ... (pattern continues)
```

## Performance Demonstrations

### Computational Examples

#### Prime Number Checker
Demonstrates computational logic.

```yeep
# Prime Number Checker
print "=== Prime Number Checker ==="
print ""

# Check if a number is prime (simplified version)
number = 17
is_prime = true

print "Checking if " + number + " is prime..."

# Check divisibility by small numbers
divisible_by_2 = number % 2 == 0 and number != 2
divisible_by_3 = number % 3 == 0 and number != 3
divisible_by_5 = number % 5 == 0 and number != 5
divisible_by_7 = number % 7 == 0 and number != 7

has_small_divisor = divisible_by_2 or divisible_by_3 or divisible_by_5 or divisible_by_7

if number <= 1 {
    is_prime = false
    print number + " is not prime (too small)"
} else if has_small_divisor {
    is_prime = false
    print number + " is not prime (has small divisors)"
} else {
    print number + " appears to be prime (basic check)"
}

print "Result: " + number + " is prime = " + is_prime
```

### Algorithm Implementations

#### Sorting Demonstration
Shows basic sorting concepts.

```yeep
# Sorting Demonstration (Bubble Sort concept)
print "=== Sorting Demo ==="
print ""

# Small array to sort manually
a = 64
b = 34
c = 25
d = 12

print "Original numbers:"
print "a = " + a
print "b = " + b  
print "c = " + c
print "d = " + d
print ""

# Manual bubble sort steps
print "Sorting steps:"

# First pass
if a > b {
    temp = a
    a = b
    b = temp
    print "Swapped a and b"
}

if b > c {
    temp = b
    b = c
    c = temp
    print "Swapped b and c"
}

if c > d {
    temp = c
    c = d
    d = temp
    print "Swapped c and d"
}

print "After first pass: " + a + ", " + b + ", " + c + ", " + d

# Continue with more passes...
```

## Real-World Applications

### Data Analysis

#### Sales Report Generator
Creates formatted sales reports.

```yeep
# Sales Report Generator
print "=== Daily Sales Report ==="
print "Date: December 15, 2024"
print "Store: Downtown Location"
print "================================"
print ""

# Sales data
morning_sales = 1250
afternoon_sales = 2100
evening_sales = 980

total_sales = morning_sales + afternoon_sales + evening_sales
average_period = total_sales / 3

# Transaction data
morning_transactions = 15
afternoon_transactions = 28
evening_transactions = 12

total_transactions = morning_transactions + afternoon_transactions + evening_transactions
average_transaction = total_sales / total_transactions

# Format report
print "SALES BY PERIOD:"
print "Morning:   $" + morning_sales + " (" + morning_transactions + " transactions)"
print "Afternoon: $" + afternoon_sales + " (" + afternoon_transactions + " transactions)"
print "Evening:   $" + evening_sales + " (" + evening_transactions + " transactions)"
print ""
print "SUMMARY:"
print "Total Sales: $" + total_sales
print "Total Transactions: " + total_transactions
print "Average per Period: $" + average_period
print "Average per Transaction: $" + average_transaction
print ""
print "Report generated successfully!"
```

### Scientific Computing

#### Unit Conversion Tool
Converts between different units of measurement.

```yeep
# Unit Conversion Tool
print "=== Unit Converter ==="
print ""

# Temperature conversion
celsius = 25
fahrenheit = celsius * 9 / 5 + 32
kelvin = celsius + 273

print "Temperature Conversions:"
print celsius + "°C = " + fahrenheit + "°F = " + kelvin + "K"
print ""

# Distance conversion
meters = 1000
kilometers = meters / 1000
feet = meters * 3.28084
miles = kilometers * 0.621371

print "Distance Conversions:"
print meters + " meters = " + kilometers + " km"
print meters + " meters = " + feet + " feet"
print kilometers + " km = " + miles + " miles"
print ""

# Weight conversion
kilograms = 70
pounds = kilograms * 2.20462
ounces = pounds * 16

print "Weight Conversions:"
print kilograms + " kg = " + pounds + " lbs = " + ounces + " oz"
```

## Getting Featured

### Submission Guidelines
To have your Yeep project featured in the showcase:

1. **Create a GitHub Gist** with your Yeep code
2. **Add documentation** explaining what your code does
3. **Include sample output** or screenshots if applicable
4. **Submit via GitHub Issues** with the "showcase" label

### Criteria for Selection
- **Educational Value**: Teaches Yeep concepts effectively
- **Code Quality**: Well-written and commented code
- **Originality**: Creative or unique use of Yeep features
- **Completeness**: Fully functional example with clear output

### Categories
- **Educational**: Teaching examples and tutorials
- **Utilities**: Practical tools and calculators
- **Games**: Interactive entertainment applications
- **Business**: Real-world business applications
- **Scientific**: Mathematical and scientific computing
- **Creative**: Art, design, and creative applications

---

## Community Contributions

Want to contribute your own Yeep projects to the showcase? We'd love to see what you've built!

- **Share Your Code**: Submit via GitHub Issues
- **Help Others**: Comment and provide feedback
- **Collaborate**: Work together on larger projects
- **Learn**: Study examples to improve your Yeep skills

Visit the [GitHub repository](https://github.com/itsthatblackhat/yeep-prolag) to submit your projects and see more community examples!

---

*The showcase is continuously updated with new community contributions. Check back regularly for fresh examples and inspiration!*
