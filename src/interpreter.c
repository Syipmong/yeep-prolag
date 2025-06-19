#include "yeep.h"

// Environment functions
Environment* create_environment(Environment* parent) {
    Environment* env = malloc(sizeof(Environment));
    env->names = malloc(sizeof(char*) * 100);
    env->values = malloc(sizeof(Value) * 100);
    env->count = 0;
    env->capacity = 100;
    env->parent = parent;
    return env;
}

void free_environment(Environment* env) {
    for (int i = 0; i < env->count; i++) {
        free(env->names[i]);
        if (env->values[i].type == VALUE_STRING) {
            free(env->values[i].data.string);
        } else if (env->values[i].type == VALUE_FUNCTION) {
            for (int j = 0; j < env->values[i].data.function.param_count; j++) {
                free(env->values[i].data.function.parameters[j]);
            }
            free(env->values[i].data.function.parameters);
        }
    }
    free(env->names);
    free(env->values);
    free(env);
}

static Value* get_variable(Environment* env, const char* name) {
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->names[i], name) == 0) {
            return &env->values[i];
        }
    }
    
    if (env->parent) {
        return get_variable(env->parent, name);
    }
    
    return NULL;
}

static void set_variable(Environment* env, const char* name, Value value) {
    // Check if variable already exists
    for (int i = 0; i < env->count; i++) {
        if (strcmp(env->names[i], name) == 0) {
            // Free old value if it's a string
            if (env->values[i].type == VALUE_STRING) {
                free(env->values[i].data.string);
            }
            env->values[i] = value;
            return;
        }
    }
    
    // Add new variable
    if (env->count >= env->capacity) {
        env->capacity *= 2;
        env->names = realloc(env->names, sizeof(char*) * env->capacity);
        env->values = realloc(env->values, sizeof(Value) * env->capacity);
    }
    
    env->names[env->count] = strdup(name);
    env->values[env->count] = value;
    env->count++;
}

// Value utility functions
Value create_number(double num) {
    Value value;
    value.type = VALUE_NUMBER;
    value.data.number = num;
    return value;
}

Value create_string(const char* str) {
    Value value;
    value.type = VALUE_STRING;
    value.data.string = strdup(str);
    return value;
}

Value create_boolean(bool val) {
    Value value;
    value.type = VALUE_BOOLEAN;
    value.data.boolean = val;
    return value;
}

Value create_null(void) {
    Value value;
    value.type = VALUE_NULL;
    return value;
}

static Value create_function(char** parameters, int param_count, ASTNode* body, Environment* closure) {
    Value value;
    value.type = VALUE_FUNCTION;
    value.data.function.parameters = malloc(sizeof(char*) * param_count);
    for (int i = 0; i < param_count; i++) {
        value.data.function.parameters[i] = strdup(parameters[i]);
    }
    value.data.function.param_count = param_count;
    value.data.function.body = body;
    value.data.function.closure = closure;
    return value;
}

void print_value(Value value) {
    switch (value.type) {
        case VALUE_NUMBER:
            printf("%.6g", value.data.number);
            break;
        case VALUE_STRING:
            printf("%s", value.data.string);
            break;
        case VALUE_BOOLEAN:
            printf("%s", value.data.boolean ? "true" : "false");
            break;
        case VALUE_FUNCTION:
            printf("<function>");
            break;
        case VALUE_NULL:
            printf("null");
            break;
    }
}

static bool is_truthy(Value value) {
    switch (value.type) {
        case VALUE_BOOLEAN:
            return value.data.boolean;
        case VALUE_NULL:
            return false;
        case VALUE_NUMBER:
            return value.data.number != 0.0;
        case VALUE_STRING:
            return strlen(value.data.string) > 0;
        default:
            return true;
    }
}

static bool values_equal(Value a, Value b) {
    if (a.type != b.type) return false;
    
    switch (a.type) {
        case VALUE_NUMBER:
            return a.data.number == b.data.number;
        case VALUE_STRING:
            return strcmp(a.data.string, b.data.string) == 0;
        case VALUE_BOOLEAN:
            return a.data.boolean == b.data.boolean;
        case VALUE_NULL:
            return true;
        default:
            return false;
    }
}

static Value string_concat(Value a, Value b) {
    char* result = malloc(strlen(a.data.string) + strlen(b.data.string) + 1);
    strcpy(result, a.data.string);
    strcat(result, b.data.string);
    
    Value value = create_string(result);
    free(result);
    return value;
}

// Exception handling for return statements
typedef struct {
    bool is_return;
    Value value;
} ReturnValue;

static ReturnValue make_return(Value value) {
    ReturnValue ret;
    ret.is_return = true;
    ret.value = value;
    return ret;
}

static ReturnValue make_normal(Value value) {
    ReturnValue ret;
    ret.is_return = false;
    ret.value = value;
    return ret;
}

static ReturnValue interpret_node(ASTNode* node, Environment* env);

static Value call_function(Value func, ASTNode** arguments, int arg_count, Environment* env) {
    if (func.type != VALUE_FUNCTION) {
        printf("Error: Attempted to call non-function\n");
        exit(1);
    }
    
    if (arg_count != func.data.function.param_count) {
        printf("Error: Function expects %d arguments, got %d\n", 
               func.data.function.param_count, arg_count);
        exit(1);
    }
    
    // Create new environment for function
    Environment* func_env = create_environment(func.data.function.closure);
    
    // Bind parameters
    for (int i = 0; i < arg_count; i++) {
        ReturnValue arg_result = interpret_node(arguments[i], env);
        if (arg_result.is_return) {
            free_environment(func_env);
            return arg_result.value;
        }
        set_variable(func_env, func.data.function.parameters[i], arg_result.value);
    }
    
    // Execute function body
    ReturnValue result = interpret_node(func.data.function.body, func_env);
    
    Value return_value = result.value;
    free_environment(func_env);
    
    return return_value;
}

static ReturnValue interpret_node(ASTNode* node, Environment* env) {
    if (!node) {
        return make_normal(create_null());
    }
    
    switch (node->type) {
        case AST_NUMBER:
            return make_normal(create_number(node->data.number));
            
        case AST_STRING:
            return make_normal(create_string(node->data.string));
            
        case AST_BOOLEAN:
            return make_normal(create_boolean(node->data.boolean));
            
        case AST_IDENTIFIER: {
            Value* var = get_variable(env, node->data.identifier.name);
            if (!var) {
                printf("Error: Undefined variable '%s'\n", node->data.identifier.name);
                exit(1);
            }
            return make_normal(*var);
        }
        
        case AST_BINARY_OP: {
            ReturnValue left_result = interpret_node(node->data.binary_op.left, env);
            if (left_result.is_return) return left_result;
            
            ReturnValue right_result = interpret_node(node->data.binary_op.right, env);
            if (right_result.is_return) return right_result;
            
            Value left = left_result.value;
            Value right = right_result.value;
            
            switch (node->data.binary_op.operator) {
                case TOKEN_PLUS:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_number(left.data.number + right.data.number));
                    } else if (left.type == VALUE_STRING && right.type == VALUE_STRING) {
                        return make_normal(string_concat(left, right));
                    } else {
                        printf("Error: Invalid operands for '+'\n");
                        exit(1);
                    }
                    
                case TOKEN_MINUS:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_number(left.data.number - right.data.number));
                    } else {
                        printf("Error: Invalid operands for '-'\n");
                        exit(1);
                    }
                    
                case TOKEN_MULTIPLY:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_number(left.data.number * right.data.number));
                    } else {
                        printf("Error: Invalid operands for '*'\n");
                        exit(1);
                    }
                    
                case TOKEN_DIVIDE:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        if (right.data.number == 0) {
                            printf("Error: Division by zero\n");
                            exit(1);
                        }
                        return make_normal(create_number(left.data.number / right.data.number));
                    } else {
                        printf("Error: Invalid operands for '/'\n");
                        exit(1);
                    }
                    
                case TOKEN_EQUAL:
                    return make_normal(create_boolean(values_equal(left, right)));
                    
                case TOKEN_NOT_EQUAL:
                    return make_normal(create_boolean(!values_equal(left, right)));
                    
                case TOKEN_LESS:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_boolean(left.data.number < right.data.number));
                    } else {
                        printf("Error: Invalid operands for '<'\n");
                        exit(1);
                    }
                    
                case TOKEN_GREATER:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_boolean(left.data.number > right.data.number));
                    } else {
                        printf("Error: Invalid operands for '>'\n");
                        exit(1);
                    }
                    
                case TOKEN_LESS_EQUAL:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_boolean(left.data.number <= right.data.number));
                    } else {
                        printf("Error: Invalid operands for '<='\n");
                        exit(1);
                    }
                    
                case TOKEN_GREATER_EQUAL:
                    if (left.type == VALUE_NUMBER && right.type == VALUE_NUMBER) {
                        return make_normal(create_boolean(left.data.number >= right.data.number));
                    } else {
                        printf("Error: Invalid operands for '>='\n");
                        exit(1);
                    }
                    
                case TOKEN_AND:
                    if (!is_truthy(left)) {
                        return make_normal(left);
                    }
                    return make_normal(right);
                    
                case TOKEN_OR:
                    if (is_truthy(left)) {
                        return make_normal(left);
                    }
                    return make_normal(right);
                    
                default:
                    printf("Error: Unknown binary operator\n");
                    exit(1);
            }
        }
        
        case AST_UNARY_OP: {
            ReturnValue operand_result = interpret_node(node->data.unary_op.operand, env);
            if (operand_result.is_return) return operand_result;
            
            Value operand = operand_result.value;
            
            switch (node->data.unary_op.operator) {
                case TOKEN_MINUS:
                    if (operand.type == VALUE_NUMBER) {
                        return make_normal(create_number(-operand.data.number));
                    } else {
                        printf("Error: Invalid operand for unary '-'\n");
                        exit(1);
                    }
                    
                case TOKEN_NOT:
                    return make_normal(create_boolean(!is_truthy(operand)));
                    
                default:
                    printf("Error: Unknown unary operator\n");
                    exit(1);
            }
        }
        
        case AST_ASSIGNMENT: {
            ReturnValue value_result = interpret_node(node->data.assignment.value, env);
            if (value_result.is_return) return value_result;
            
            set_variable(env, node->data.assignment.variable, value_result.value);
            return make_normal(value_result.value);
        }
        
        case AST_FUNCTION_CALL: {
            Value* func = get_variable(env, node->data.function_call.name);
            if (!func) {
                printf("Error: Undefined function '%s'\n", node->data.function_call.name);
                exit(1);
            }
            
            Value result = call_function(*func, node->data.function_call.arguments, 
                                       node->data.function_call.arg_count, env);
            return make_normal(result);
        }
        
        case AST_FUNCTION_DEF: {
            Value func = create_function(node->data.function_def.parameters, 
                                       node->data.function_def.param_count,
                                       node->data.function_def.body, env);
            set_variable(env, node->data.function_def.name, func);
            return make_normal(func);
        }
        
        case AST_IF_STATEMENT: {
            ReturnValue condition_result = interpret_node(node->data.if_statement.condition, env);
            if (condition_result.is_return) return condition_result;
            
            if (is_truthy(condition_result.value)) {
                return interpret_node(node->data.if_statement.then_branch, env);
            } else if (node->data.if_statement.else_branch) {
                return interpret_node(node->data.if_statement.else_branch, env);
            }
            return make_normal(create_null());
        }
        
        case AST_WHILE_STATEMENT: {
            Value result = create_null();
            
            while (true) {
                ReturnValue condition_result = interpret_node(node->data.while_statement.condition, env);
                if (condition_result.is_return) return condition_result;
                
                if (!is_truthy(condition_result.value)) {
                    break;
                }
                
                ReturnValue body_result = interpret_node(node->data.while_statement.body, env);
                if (body_result.is_return) return body_result;
                
                result = body_result.value;
            }
            
            return make_normal(result);
        }
        
        case AST_BLOCK: {
            Value result = create_null();
            
            for (int i = 0; i < node->data.block.statement_count; i++) {
                ReturnValue stmt_result = interpret_node(node->data.block.statements[i], env);
                if (stmt_result.is_return) return stmt_result;
                
                result = stmt_result.value;
            }
            
            return make_normal(result);
        }
        
        case AST_RETURN_STATEMENT: {
            if (node->data.return_statement.value) {
                ReturnValue value_result = interpret_node(node->data.return_statement.value, env);
                if (value_result.is_return) return value_result;
                return make_return(value_result.value);
            } else {
                return make_return(create_null());
            }
        }
        
        case AST_PRINT_STATEMENT: {
            ReturnValue expr_result = interpret_node(node->data.print_statement.expression, env);
            if (expr_result.is_return) return expr_result;
            
            print_value(expr_result.value);
            printf("\n");
            return make_normal(create_null());
        }
        
        default:
            printf("Error: Unknown AST node type\n");
            exit(1);
    }
}

Value interpret(ASTNode* node, Environment* env) {
    ReturnValue result = interpret_node(node, env);
    return result.value;
}
