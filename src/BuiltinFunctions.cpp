#include "BuiltinFunctions.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>
#include <fstream>
#include <cstdlib>
#include <cstdio>

namespace yeep {

    std::unordered_map<std::string, BuiltinFunction> BuiltinFunctions::functions_;
    bool BuiltinFunctions::initialized_ = false;

    void BuiltinFunctions::initialize() {
        if (initialized_) return;
        
        // Math functions
        functions_["abs"] = abs;
        functions_["sqrt"] = sqrt;
        functions_["pow"] = pow;
        functions_["max"] = max;
        functions_["min"] = min;
        functions_["floor"] = floor;
        functions_["ceil"] = ceil;
        functions_["round"] = round;
        functions_["random"] = random;
        
        // String functions
        functions_["length"] = length;
        functions_["len"] = length;  // alias
        functions_["substring"] = substring;
        functions_["substr"] = substring;  // alias
        functions_["uppercase"] = uppercase;
        functions_["upper"] = uppercase;  // alias
        functions_["lowercase"] = lowercase;
        functions_["lower"] = lowercase;  // alias
        functions_["contains"] = contains;
        
        // Type functions
        functions_["type"] = type;
        functions_["toString"] = toString;
        functions_["str"] = toString;  // alias
        functions_["toNumber"] = toNumber;
        functions_["num"] = toNumber;  // alias
          // I/O functions
        functions_["input"] = input;
        functions_["readFile"] = readFile;
        functions_["readfile"] = readFile;  // alias
        functions_["writeFile"] = writeFile;
        functions_["writefile"] = writeFile;  // alias
        functions_["fileExists"] = fileExists;
        functions_["exists"] = fileExists;  // alias
        
        // System functions
        functions_["env"] = env;
        functions_["environment"] = env;  // alias
        functions_["now"] = currentTime;
        functions_["time"] = currentTime;  // alias
        functions_["exec"] = exec;
        functions_["system"] = exec;  // alias
        
        // Array functions
        functions_["push"] = push;
        functions_["pop"] = pop;
        functions_["size"] = size;
        functions_["get"] = get;
        functions_["set"] = set;
        
        initialized_ = true;
    }

    bool BuiltinFunctions::isBuiltin(const std::string& name) {
        initialize();
        return functions_.find(name) != functions_.end();
    }

    Value BuiltinFunctions::call(const std::string& name, const std::vector<Value>& args) {
        initialize();
        auto it = functions_.find(name);
        if (it != functions_.end()) {
            return it->second(args);
        }
        throw std::runtime_error("Unknown builtin function: " + name);
    }

    // Math functions
    Value BuiltinFunctions::abs(const std::vector<Value>& args) {
        checkArgCount(args, 1, "abs");
        if (!args[0].isNumber()) {
            throw std::runtime_error("abs() requires a number");
        }
        return Value(std::abs(args[0].getNumber()));
    }

    Value BuiltinFunctions::sqrt(const std::vector<Value>& args) {
        checkArgCount(args, 1, "sqrt");
        if (!args[0].isNumber()) {
            throw std::runtime_error("sqrt() requires a number");
        }
        double val = args[0].getNumber();
        if (val < 0) {
            throw std::runtime_error("sqrt() of negative number");
        }
        return Value(std::sqrt(val));
    }

    Value BuiltinFunctions::pow(const std::vector<Value>& args) {
        checkArgCount(args, 2, "pow");
        if (!args[0].isNumber() || !args[1].isNumber()) {
            throw std::runtime_error("pow() requires two numbers");
        }
        return Value(std::pow(args[0].getNumber(), args[1].getNumber()));
    }

    Value BuiltinFunctions::max(const std::vector<Value>& args) {
        if (args.empty()) {
            throw std::runtime_error("max() requires at least one argument");
        }
        
        double maxVal = args[0].getNumber();
        for (size_t i = 1; i < args.size(); ++i) {
            if (!args[i].isNumber()) {
                throw std::runtime_error("max() requires all arguments to be numbers");
            }
            maxVal = std::max(maxVal, args[i].getNumber());
        }
        return Value(maxVal);
    }

    Value BuiltinFunctions::min(const std::vector<Value>& args) {
        if (args.empty()) {
            throw std::runtime_error("min() requires at least one argument");
        }
        
        double minVal = args[0].getNumber();
        for (size_t i = 1; i < args.size(); ++i) {
            if (!args[i].isNumber()) {
                throw std::runtime_error("min() requires all arguments to be numbers");
            }
            minVal = std::min(minVal, args[i].getNumber());
        }
        return Value(minVal);
    }

    Value BuiltinFunctions::floor(const std::vector<Value>& args) {
        checkArgCount(args, 1, "floor");
        if (!args[0].isNumber()) {
            throw std::runtime_error("floor() requires a number");
        }
        return Value(std::floor(args[0].getNumber()));
    }

    Value BuiltinFunctions::ceil(const std::vector<Value>& args) {
        checkArgCount(args, 1, "ceil");
        if (!args[0].isNumber()) {
            throw std::runtime_error("ceil() requires a number");
        }
        return Value(std::ceil(args[0].getNumber()));
    }

    Value BuiltinFunctions::round(const std::vector<Value>& args) {
        checkArgCount(args, 1, "round");
        if (!args[0].isNumber()) {
            throw std::runtime_error("round() requires a number");
        }
        return Value(std::round(args[0].getNumber()));
    }

    Value BuiltinFunctions::random(const std::vector<Value>& args) {
        checkArgCount(args, 0, "random");
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<> dis(0.0, 1.0);
        return Value(dis(gen));
    }

    // String functions
    Value BuiltinFunctions::length(const std::vector<Value>& args) {
        checkArgCount(args, 1, "length");
        if (!args[0].isString()) {
            throw std::runtime_error("length() requires a string");
        }
        return Value(static_cast<double>(args[0].getString().length()));
    }

    Value BuiltinFunctions::substring(const std::vector<Value>& args) {
        if (args.size() != 2 && args.size() != 3) {
            throw std::runtime_error("substring() requires 2 or 3 arguments");
        }
        if (!args[0].isString() || !args[1].isNumber()) {
            throw std::runtime_error("substring() requires string and number arguments");
        }
        
        const std::string& str = args[0].getString();
        size_t start = static_cast<size_t>(args[1].getNumber());
        size_t end = str.length();
        
        if (args.size() == 3) {
            if (!args[2].isNumber()) {
                throw std::runtime_error("substring() end index must be a number");
            }
            end = static_cast<size_t>(args[2].getNumber());
        }
        
        if (start >= str.length()) return Value("");
        if (end > str.length()) end = str.length();
        if (end <= start) return Value("");
        
        return Value(str.substr(start, end - start));
    }

    Value BuiltinFunctions::uppercase(const std::vector<Value>& args) {
        checkArgCount(args, 1, "uppercase");
        if (!args[0].isString()) {
            throw std::runtime_error("uppercase() requires a string");
        }
        
        std::string result = args[0].getString();
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return Value(result);
    }

    Value BuiltinFunctions::lowercase(const std::vector<Value>& args) {
        checkArgCount(args, 1, "lowercase");
        if (!args[0].isString()) {
            throw std::runtime_error("lowercase() requires a string");
        }
        
        std::string result = args[0].getString();
        std::transform(result.begin(), result.end(), result.begin(), ::tolower);
        return Value(result);
    }

    Value BuiltinFunctions::contains(const std::vector<Value>& args) {
        checkArgCount(args, 2, "contains");
        if (!args[0].isString() || !args[1].isString()) {
            throw std::runtime_error("contains() requires two strings");
        }
        
        const std::string& str = args[0].getString();
        const std::string& substr = args[1].getString();
        return Value(str.find(substr) != std::string::npos);
    }

    // Type functions
    Value BuiltinFunctions::type(const std::vector<Value>& args) {
        checkArgCount(args, 1, "type");
        const Value& val = args[0];
        
        if (val.isNil()) return Value("nil");
        if (val.isBool()) return Value("boolean");
        if (val.isNumber()) return Value("number");
        if (val.isString()) return Value("string");
        return Value("unknown");
    }

    Value BuiltinFunctions::toString(const std::vector<Value>& args) {
        checkArgCount(args, 1, "toString");
        return Value(args[0].toString());
    }

    Value BuiltinFunctions::toNumber(const std::vector<Value>& args) {
        checkArgCount(args, 1, "toNumber");
        const Value& val = args[0];
        
        if (val.isNumber()) return val;
        if (val.isString()) {
            try {
                return Value(std::stod(val.getString()));
            } catch (...) {
                throw std::runtime_error("Cannot convert string to number");
            }
        }
        if (val.isBool()) return Value(val.getBool() ? 1.0 : 0.0);
        
        throw std::runtime_error("Cannot convert value to number");
    }

    // I/O functions
    Value BuiltinFunctions::input(const std::vector<Value>& args) {
        if (args.size() > 1) {
            throw std::runtime_error("input() takes at most 1 argument");
        }
        
        if (args.size() == 1) {
            std::cout << args[0].toString();
        }
        
        std::string line;
        std::getline(std::cin, line);
        return Value(line);
    }

    // Array functions
    Value BuiltinFunctions::push(const std::vector<Value>& args) {
        if (args.size() < 2) {
            throw std::runtime_error("push() expects at least 2 arguments");
        }
        
        if (!args[0].isArray()) {
            throw std::runtime_error("push() first argument must be an array");
        }
        
        // Note: This creates a new array rather than modifying in place
        // In a real implementation, we'd need reference semantics
        Array arr = args[0].getArray();
        for (size_t i = 1; i < args.size(); ++i) {
            arr.push_back(args[i]);
        }
        
        return Value(arr);
    }

    Value BuiltinFunctions::pop(const std::vector<Value>& args) {
        if (args.size() != 1) {
            throw std::runtime_error("pop() expects 1 argument");
        }
        
        if (!args[0].isArray()) {
            throw std::runtime_error("pop() argument must be an array");
        }
        
        Array arr = args[0].getArray();
        if (arr.empty()) {
            throw std::runtime_error("Cannot pop from empty array");
        }
        
        Value result = arr.back();
        arr.pop_back();
        
        return result;
    }

    Value BuiltinFunctions::size(const std::vector<Value>& args) {
        if (args.size() != 1) {
            throw std::runtime_error("size() expects 1 argument");
        }
        
        if (args[0].isArray()) {
            return Value(static_cast<double>(args[0].getArray().size()));
        } else if (args[0].isString()) {
            return Value(static_cast<double>(args[0].getString().size()));
        } else {
            throw std::runtime_error("size() argument must be an array or string");
        }
    }

    Value BuiltinFunctions::get(const std::vector<Value>& args) {
        if (args.size() != 2) {
            throw std::runtime_error("get() expects 2 arguments");
        }
        
        if (!args[0].isArray()) {
            throw std::runtime_error("get() first argument must be an array");
        }
        
        if (!args[1].isNumber()) {
            throw std::runtime_error("get() second argument must be a number");
        }
        
        const Array& arr = args[0].getArray();
        int index = static_cast<int>(args[1].getNumber());
        
        if (index < 0 || index >= static_cast<int>(arr.size())) {
            throw std::runtime_error("Array index out of bounds");
        }
        
        return arr[index];
    }

    Value BuiltinFunctions::set(const std::vector<Value>& args) {
        if (args.size() != 3) {
            throw std::runtime_error("set() expects 3 arguments");
        }
        
        if (!args[0].isArray()) {
            throw std::runtime_error("set() first argument must be an array");
        }
        
        if (!args[1].isNumber()) {
            throw std::runtime_error("set() second argument must be a number");
        }
        
        // Note: This would need reference semantics to work properly
        // For now, it returns a modified copy
        Array arr = args[0].getArray();
        int index = static_cast<int>(args[1].getNumber());
        
        if (index < 0 || index >= static_cast<int>(arr.size())) {
            throw std::runtime_error("Array index out of bounds");
        }
        
        arr[index] = args[2];
        return Value(arr);
    }    void BuiltinFunctions::checkArgCount(const std::vector<Value>& args, size_t expected, const std::string& name) {
        if (args.size() != expected) {
            throw std::runtime_error(name + "() expects " + std::to_string(expected) + 
                                   " arguments, got " + std::to_string(args.size()));
        }
    }

    // File I/O functions
    Value BuiltinFunctions::readFile(const std::vector<Value>& args) {
        checkArgCount(args, 1, "readFile");
        
        if (!args[0].isString()) {
            throw std::runtime_error("readFile() argument must be a string");
        }
        
        std::ifstream file(args[0].getString());
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + args[0].getString());
        }
        
        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        
        return Value(content);
    }

    Value BuiltinFunctions::writeFile(const std::vector<Value>& args) {
        checkArgCount(args, 2, "writeFile");
        
        if (!args[0].isString()) {
            throw std::runtime_error("writeFile() first argument must be a string (filename)");
        }
        if (!args[1].isString()) {
            throw std::runtime_error("writeFile() second argument must be a string (content)");
        }
        
        std::ofstream file(args[0].getString());
        if (!file.is_open()) {
            throw std::runtime_error("Failed to create/open file: " + args[0].getString());
        }
        
        file << args[1].getString();
        file.close();
        
        return Value(true);  // Success
    }

    Value BuiltinFunctions::fileExists(const std::vector<Value>& args) {
        checkArgCount(args, 1, "fileExists");
        
        if (!args[0].isString()) {
            throw std::runtime_error("fileExists() argument must be a string");
        }
        
        std::ifstream file(args[0].getString());
        bool exists = file.good();
        file.close();
        
        return Value(exists);
    }

    // System functions
    Value BuiltinFunctions::env(const std::vector<Value>& args) {
        checkArgCount(args, 1, "env");
        
        if (!args[0].isString()) {
            throw std::runtime_error("env() argument must be a string");
        }
        
        const char* envVar = std::getenv(args[0].getString().c_str());
        if (envVar == nullptr) {
            return Value();  // nil
        }
        
        return Value(std::string(envVar));
    }

    Value BuiltinFunctions::currentTime(const std::vector<Value>& args) {
        if (args.size() != 0) {
            throw std::runtime_error("now() expects no arguments");
        }
        
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        
        return Value(static_cast<double>(time_t));
    }

    Value BuiltinFunctions::exec(const std::vector<Value>& args) {
        checkArgCount(args, 1, "exec");
        
        if (!args[0].isString()) {
            throw std::runtime_error("exec() argument must be a string");
        }
        
        int result = std::system(args[0].getString().c_str());
        return Value(static_cast<double>(result));
    }

} // namespace yeep
