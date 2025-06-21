#include "core/BuiltinFunctions.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <random>
#include <chrono>
#include <stdexcept>

namespace yeep {
    
    std::map<std::string, BuiltinFunction> BuiltinFunctions::functions_;
    bool BuiltinFunctions::initialized_ = false;
    
    void BuiltinFunctions::initialize() {
        if (initialized_) return;
        
        // Mathematical functions
        functions_["abs"] = abs;
        functions_["sqrt"] = sqrt;
        functions_["pow"] = pow;
        functions_["max"] = max;
        functions_["min"] = min;
        functions_["floor"] = floor;
        functions_["ceil"] = ceil;
        functions_["round"] = round;
        
        // String functions
        functions_["length"] = length;
        functions_["len"] = length;  // Alias
        functions_["substring"] = substring;
        functions_["substr"] = substring;  // Alias
        functions_["uppercase"] = uppercase;
        functions_["upper"] = uppercase;  // Alias
        functions_["lowercase"] = lowercase;
        functions_["lower"] = lowercase;  // Alias
        functions_["contains"] = contains;
        functions_["startsWith"] = startsWith;
        functions_["endsWith"] = endsWith;
        
        // Type conversion functions
        functions_["toString"] = toString;
        functions_["str"] = toString;  // Alias
        functions_["toNumber"] = toNumber;
        functions_["num"] = toNumber;  // Alias
        functions_["toBoolean"] = toBoolean;
        functions_["bool"] = toBoolean;  // Alias
        
        // Utility functions
        functions_["type"] = type;
        functions_["input"] = input;
        functions_["random"] = random;
        functions_["rand"] = random;  // Alias
        functions_["time"] = time;
        
        initialized_ = true;
    }
    
    bool BuiltinFunctions::isBuiltin(const std::string& name) {
        initialize();
        return functions_.find(name) != functions_.end();
    }
    
    BuiltinFunction BuiltinFunctions::getBuiltin(const std::string& name) {
        initialize();
        auto it = functions_.find(name);
        if (it != functions_.end()) {
            return it->second;
        }
        throw std::runtime_error("Unknown builtin function: " + name);
    }
    
    std::vector<std::string> BuiltinFunctions::getAllFunctionNames() {
        initialize();
        std::vector<std::string> names;
        for (const auto& pair : functions_) {
            names.push_back(pair.first);
        }
        std::sort(names.begin(), names.end());
        return names;
    }
    
    // Mathematical functions
    TokenValue BuiltinFunctions::abs(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "abs");
        const auto& arg = args[0];
        
        if (arg.isInt()) {
            return TokenValue(std::abs(arg.getInt()));
        } else if (arg.isDouble()) {
            return TokenValue(std::abs(arg.getDouble()));
        }
        throw std::runtime_error("abs() requires a number");
    }
    
    TokenValue BuiltinFunctions::sqrt(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "sqrt");
        const auto& arg = args[0];
        
        if (arg.isNumber()) {
            double value = arg.isInt() ? arg.getInt() : arg.getDouble();
            if (value < 0) {
                throw std::runtime_error("sqrt() of negative number");
            }
            return TokenValue(std::sqrt(value));
        }
        throw std::runtime_error("sqrt() requires a number");
    }
    
    TokenValue BuiltinFunctions::pow(const std::vector<TokenValue>& args) {
        validateArgCount(args, 2, "pow");
        const auto& base = args[0];
        const auto& exponent = args[1];
        
        if (base.isNumber() && exponent.isNumber()) {
            double baseVal = base.isInt() ? base.getInt() : base.getDouble();
            double expVal = exponent.isInt() ? exponent.getInt() : exponent.getDouble();
            return TokenValue(std::pow(baseVal, expVal));
        }
        throw std::runtime_error("pow() requires two numbers");
    }
    
    TokenValue BuiltinFunctions::max(const std::vector<TokenValue>& args) {
        if (args.empty()) {
            throw std::runtime_error("max() requires at least one argument");
        }
        
        TokenValue maxVal = args[0];
        for (size_t i = 1; i < args.size(); ++i) {
            const auto& current = args[i];
            if (current.isNumber() && maxVal.isNumber()) {
                double currentVal = current.isInt() ? current.getInt() : current.getDouble();
                double maxValNum = maxVal.isInt() ? maxVal.getInt() : maxVal.getDouble();
                if (currentVal > maxValNum) {
                    maxVal = current;
                }
            } else {
                throw std::runtime_error("max() requires all arguments to be numbers");
            }
        }
        return maxVal;
    }
    
    TokenValue BuiltinFunctions::min(const std::vector<TokenValue>& args) {
        if (args.empty()) {
            throw std::runtime_error("min() requires at least one argument");
        }
        
        TokenValue minVal = args[0];
        for (size_t i = 1; i < args.size(); ++i) {
            const auto& current = args[i];
            if (current.isNumber() && minVal.isNumber()) {
                double currentVal = current.isInt() ? current.getInt() : current.getDouble();
                double minValNum = minVal.isInt() ? minVal.getInt() : minVal.getDouble();
                if (currentVal < minValNum) {
                    minVal = current;
                }
            } else {
                throw std::runtime_error("min() requires all arguments to be numbers");
            }
        }
        return minVal;
    }
    
    TokenValue BuiltinFunctions::floor(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "floor");
        const auto& arg = args[0];
        
        if (arg.isNumber()) {
            double value = arg.isInt() ? arg.getInt() : arg.getDouble();
            return TokenValue(static_cast<int>(std::floor(value)));
        }
        throw std::runtime_error("floor() requires a number");
    }
    
    TokenValue BuiltinFunctions::ceil(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "ceil");
        const auto& arg = args[0];
        
        if (arg.isNumber()) {
            double value = arg.isInt() ? arg.getInt() : arg.getDouble();
            return TokenValue(static_cast<int>(std::ceil(value)));
        }
        throw std::runtime_error("ceil() requires a number");
    }
    
    TokenValue BuiltinFunctions::round(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "round");
        const auto& arg = args[0];
        
        if (arg.isNumber()) {
            double value = arg.isInt() ? arg.getInt() : arg.getDouble();
            return TokenValue(static_cast<int>(std::round(value)));
        }
        throw std::runtime_error("round() requires a number");
    }
    
    // String functions
    TokenValue BuiltinFunctions::length(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "length");
        const auto& arg = args[0];
        
        if (arg.isString()) {
            return TokenValue(static_cast<int>(arg.getString().length()));
        }
        throw std::runtime_error("length() requires a string");
    }
    
    TokenValue BuiltinFunctions::substring(const std::vector<TokenValue>& args) {
        validateArgCount(args, 2, 3, "substring");
        const auto& str = args[0];
        const auto& start = args[1];
        
        if (!str.isString() || !start.isInt()) {
            throw std::runtime_error("substring() requires (string, start_index) or (string, start_index, length)");
        }
        
        const std::string& text = str.getString();
        int startIdx = start.getInt();
        
        if (startIdx < 0 || startIdx >= static_cast<int>(text.length())) {
            throw std::runtime_error("substring() start index out of bounds");
        }
        
        if (args.size() == 3) {
            const auto& length = args[2];
            if (!length.isInt()) {
                throw std::runtime_error("substring() length must be an integer");
            }
            int len = length.getInt();
            if (len < 0) {
                throw std::runtime_error("substring() length cannot be negative");
            }
            return TokenValue(text.substr(startIdx, len));
        } else {
            return TokenValue(text.substr(startIdx));
        }
    }
    
    TokenValue BuiltinFunctions::uppercase(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "uppercase");
        const auto& arg = args[0];
        
        if (arg.isString()) {
            std::string result = arg.getString();
            std::transform(result.begin(), result.end(), result.begin(), ::toupper);
            return TokenValue(result);
        }
        throw std::runtime_error("uppercase() requires a string");
    }
    
    TokenValue BuiltinFunctions::lowercase(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "lowercase");
        const auto& arg = args[0];
        
        if (arg.isString()) {
            std::string result = arg.getString();
            std::transform(result.begin(), result.end(), result.begin(), ::tolower);
            return TokenValue(result);
        }
        throw std::runtime_error("lowercase() requires a string");
    }
    
    TokenValue BuiltinFunctions::contains(const std::vector<TokenValue>& args) {
        validateArgCount(args, 2, "contains");
        const auto& str = args[0];
        const auto& substr = args[1];
        
        if (str.isString() && substr.isString()) {
            bool result = str.getString().find(substr.getString()) != std::string::npos;
            return TokenValue(result);
        }
        throw std::runtime_error("contains() requires two strings");
    }
    
    TokenValue BuiltinFunctions::startsWith(const std::vector<TokenValue>& args) {
        validateArgCount(args, 2, "startsWith");
        const auto& str = args[0];
        const auto& prefix = args[1];
        
        if (str.isString() && prefix.isString()) {
            const std::string& text = str.getString();
            const std::string& pre = prefix.getString();
            bool result = text.length() >= pre.length() && 
                         text.substr(0, pre.length()) == pre;
            return TokenValue(result);
        }
        throw std::runtime_error("startsWith() requires two strings");
    }
    
    TokenValue BuiltinFunctions::endsWith(const std::vector<TokenValue>& args) {
        validateArgCount(args, 2, "endsWith");
        const auto& str = args[0];
        const auto& suffix = args[1];
        
        if (str.isString() && suffix.isString()) {
            const std::string& text = str.getString();
            const std::string& suf = suffix.getString();
            bool result = text.length() >= suf.length() && 
                         text.substr(text.length() - suf.length()) == suf;
            return TokenValue(result);
        }
        throw std::runtime_error("endsWith() requires two strings");
    }
    
    // Type conversion functions
    TokenValue BuiltinFunctions::toString(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "toString");
        const auto& arg = args[0];
        
        if (arg.isString()) {
            return arg;
        } else if (arg.isInt()) {
            return TokenValue(std::to_string(arg.getInt()));
        } else if (arg.isDouble()) {
            return TokenValue(std::to_string(arg.getDouble()));        } else if (arg.isBool()) {
            return TokenValue(arg.getBool() ? "true" : "false");
        }
        return TokenValue("null");
    }
    
    TokenValue BuiltinFunctions::toNumber(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "toNumber");
        const auto& arg = args[0];
        
        if (arg.isNumber()) {
            return arg;
        } else if (arg.isString()) {
            const std::string& str = arg.getString();
            try {
                if (str.find('.') != std::string::npos) {
                    return TokenValue(std::stod(str));
                } else {
                    return TokenValue(std::stoi(str));
                }
            } catch (const std::exception&) {
                throw std::runtime_error("Cannot convert '" + str + "' to number");
            }        } else if (arg.isBool()) {
            return TokenValue(arg.getBool() ? 1 : 0);
        }
        throw std::runtime_error("Cannot convert to number");
    }
    
    TokenValue BuiltinFunctions::toBoolean(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "toBoolean");
        const auto& arg = args[0];
        
        if (arg.isBool()) {
            return arg;
        } else if (arg.isNumber()) {
            if (arg.isInt()) {
                return TokenValue(arg.getInt() != 0);
            } else {
                return TokenValue(arg.getDouble() != 0.0);
            }
        } else if (arg.isString()) {
            const std::string& str = arg.getString();
            return TokenValue(!str.empty() && str != "false" && str != "0");
        }
        return TokenValue(false);
    }
    
    // Utility functions
    TokenValue BuiltinFunctions::type(const std::vector<TokenValue>& args) {
        validateArgCount(args, 1, "type");
        const auto& arg = args[0];
        
        if (arg.isString()) {
            return TokenValue("string");
        } else if (arg.isInt()) {
            return TokenValue("integer");
        } else if (arg.isDouble()) {
            return TokenValue("double");
        } else if (arg.isBool()) {
            return TokenValue("boolean");
        }
        return TokenValue("unknown");
    }
    
    TokenValue BuiltinFunctions::input(const std::vector<TokenValue>& args) {
        validateArgCount(args, 0, 1, "input");
        
        // Print prompt if provided
        if (!args.empty() && args[0].isString()) {
            std::cout << args[0].getString();
        }
        
        std::string line;
        std::getline(std::cin, line);
        return TokenValue(line);
    }
    
    TokenValue BuiltinFunctions::random(const std::vector<TokenValue>& args) {
        validateArgCount(args, 0, 2, "random");
        
        static std::random_device rd;
        static std::mt19937 gen(rd());
        
        if (args.empty()) {
            // Return random double between 0 and 1
            std::uniform_real_distribution<> dis(0.0, 1.0);
            return TokenValue(dis(gen));
        } else if (args.size() == 1) {
            // Return random integer between 0 and max-1
            const auto& maxArg = args[0];
            if (!maxArg.isInt()) {
                throw std::runtime_error("random() max value must be an integer");
            }
            int max = maxArg.getInt();
            if (max <= 0) {
                throw std::runtime_error("random() max value must be positive");
            }
            std::uniform_int_distribution<> dis(0, max - 1);
            return TokenValue(dis(gen));
        } else {
            // Return random integer between min and max
            const auto& minArg = args[0];
            const auto& maxArg = args[1];
            if (!minArg.isInt() || !maxArg.isInt()) {
                throw std::runtime_error("random() min and max values must be integers");
            }
            int min = minArg.getInt();
            int max = maxArg.getInt();
            if (min >= max) {
                throw std::runtime_error("random() min must be less than max");
            }
            std::uniform_int_distribution<> dis(min, max);
            return TokenValue(dis(gen));
        }
    }
    
    TokenValue BuiltinFunctions::time(const std::vector<TokenValue>& args) {
        validateArgCount(args, 0, "time");
        
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        return TokenValue(static_cast<int>(timestamp));
    }
    
    // Helper functions
    void BuiltinFunctions::validateArgCount(const std::vector<TokenValue>& args, size_t expected, const std::string& functionName) {
        if (args.size() != expected) {
            throw std::runtime_error(functionName + "() expects " + std::to_string(expected) + 
                                   " argument(s), got " + std::to_string(args.size()));
        }
    }
    
    void BuiltinFunctions::validateArgCount(const std::vector<TokenValue>& args, size_t min, size_t max, const std::string& functionName) {
        if (args.size() < min || args.size() > max) {
            throw std::runtime_error(functionName + "() expects " + std::to_string(min) + 
                                   "-" + std::to_string(max) + " argument(s), got " + std::to_string(args.size()));
        }
    }
    
} // namespace yeep
