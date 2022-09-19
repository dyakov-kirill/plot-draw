#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

char *get_string() {
    char *string;
    int symbol, length = 1, i = 1;
    string = realloc(NULL, sizeof(*string) * length);
    symbol = getchar();
    string[0] = symbol;
    while (symbol != '\n') {
        symbol = getchar();
        if (symbol != ' ' && symbol != '\n') {
            length++;
            char *tmp = realloc(string, sizeof(*string) * length);
            if (tmp == NULL) {
                free(tmp);
            } else {
                string = tmp;
            }
            string[i++] = symbol;
        }
    }
    return string;
}

t_token **string_to_tokens(char *string, int *array_size, int *error) {
    t_token **token_array = malloc(sizeof(t_token *));
    int operator_counter = 0, num_counter = 0, arity = 0, priority = 0,
        open_brackets = 0, close_brackets = 0, fun_len = 0;
    for (int i = 0; i < (int)strlen(string); i++) {
        int type = -1;
        if (is_number(string[i], &type, &priority)) {
            token_array =
                add_number(token_array, array_size, string, &i, &arity, &type,
                           &priority, &operator_counter, error, &num_counter);
        } else if (is_operator(string[i], &arity, &type, &priority,
                               &operator_counter, error)) {
            token_array =
                add_operator(token_array, array_size, string, i, &type,
                             &priority, &operator_counter, error);
        } else if (is_bracket(string[i], &type, &priority, &open_brackets,
                              &close_brackets, error)) {
            token_array = add_bracket(token_array, array_size, string, i, &type,
                                      &priority);
        } else if (is_function(string[i], string[i + 1], &fun_len, &type,
                               &priority)) {
            token_array =
                add_function(token_array, array_size, string, &i, &type,
                             &priority, &operator_counter, &fun_len, error);
        } else if (is_variable(string[i], &type, &priority)) {
            token_array =
                add_variable(token_array, array_size, string, i, &arity, &type,
                             &priority, &operator_counter, error);
        } else {
            *error = INCORRECT_SYMBOLS;
        }
    }
    if (open_brackets != close_brackets) {
        *error = BRACKETS_ERROR;
    }
    return token_array;
}

t_token **add_variable(t_token **token_array, int *array_size, char *string,
                       int i, int *arity, int *type, int *priority,
                       int *operator_counter, int *error) {
    *arity = 1;
    *operator_counter = 0;
    char *var_str = malloc(2 * sizeof(char));
    var_str[0] = string[i];
    var_str[1] = '\0';
    token_array[*array_size] = create_token(var_str, *type, *priority);
    (*array_size)++;
    token_array = realloc(token_array, sizeof(t_token *) * ((*array_size) + 1));
    if (i != 0 && (is_variable(string[i - 1], type, priority) ||
                   is_number(string[i - 1], type, priority)))
        *error = VARIABLE_ERROR;
    free(var_str);
    return token_array;
}

t_token **add_function(t_token **token_array, int *array_size,
                       const char *string, int *i, int *type, int *priority,
                       int *operator_counter, const int *fun_len, int *error) {
    *operator_counter = 0;
    char *fun_str = malloc((*fun_len + 1) * sizeof(char));
    int j = *i;
    for (int k = 0; k < *fun_len; k++) {
        fun_str[k] = string[j];
        j++;
    }
    fun_str[*fun_len] = '\0';
    *i = j - 1;
    token_array[*array_size] = create_token(fun_str, *type, *priority);
    (*array_size)++;
    token_array = realloc(token_array, sizeof(t_token *) * ((*array_size) + 1));
    free(fun_str);
    if (string[j] != '(') *error = FUNCTION_ERROR;
    return token_array;
}

t_token **add_bracket(t_token **token_array, int *array_size,
                      const char *string, int i, int *type, int *priority) {
    char *br_str = malloc(2 * sizeof(char));
    br_str[0] = string[i];
    br_str[1] = '\0';
    token_array[*array_size] = create_token(br_str, *type, *priority);
    (*array_size)++;
    token_array = realloc(token_array, sizeof(t_token *) * ((*array_size) + 1));
    free(br_str);
    return token_array;
}

t_token **add_operator(t_token **token_array, int *array_size,
                       const char *string, int i, int *type, int *priority,
                       int *operator_counter, int *error) {
    (*operator_counter)++;
    char *op_str = malloc(2 * sizeof(char));
    op_str[0] = string[i];
    op_str[1] = '\0';
    token_array[*array_size] = create_token(op_str, *type, *priority);
    (*array_size)++;
    token_array = realloc(token_array, sizeof(t_token *) * ((*array_size) + 1));
    if (string[i + 1] == '\0') *error = OPERATOR_ERROR;
    free(op_str);
    return token_array;
}

t_token **add_number(t_token **token_array, int *array_size, char *string,
                     int *i, int *arity, int *type, int *priority,
                     int *operator_counter, int *error, int *num_counter) {
    int j = *i, num_len = 0;
    char *num_str = malloc(sizeof(char));
    int dot_counter = 0, digit_counter = 0;
    if (*i != 0 && (is_variable(string[j - 1], type, priority) ||
                    is_number(string[j - 1], type, priority)))
        *error = NUMBER_ERROR;
    while (string[j] != '\0' &&
           (is_number(string[j], type, priority) || string[j] == '.')) {
        if (string[j] == '.' && dot_counter == 0) {
            dot_counter++;
        } else if (string[j] != '.') {
            digit_counter++;
        }
        num_len++;
        char *tmp = realloc(num_str, sizeof(*num_str) * num_len);
        if (tmp == NULL) {
            free(tmp);
        } else {
            num_str = tmp;
        }
        num_str[num_len - 1] = string[j];
        j++;
        if (dot_counter > 0 || dot_counter > digit_counter) {
            *error = NUMBER_ERROR;
            string[j] = '\0';
        }
    }
    num_str[num_len] = '\0';
    *i = j - 1;
    token_array[*array_size] = create_token(num_str, *type, *priority);
    (*array_size)++;
    token_array = realloc(token_array, sizeof(t_token *) * ((*array_size) + 1));
    *operator_counter = 0;
    (*num_counter)++;
    *arity = 1;
    free(num_str);
    return token_array;
}

t_token *create_token(char *value, int type, int priority) {
    t_token *new_token = malloc(sizeof(t_token));
    strcpy(new_token->value, value);
    new_token->type = type;
    new_token->priority = priority;
    return new_token;
}

int is_number(char symbol, int *type, int *priority) {
    int res = 0;
    if (symbol >= '0' && symbol <= '9') {
        res = 1;
        *type = 0;
        *priority = -1;
    }
    if (symbol == '.') {
        res = 1;
    }
    return res;
}

int is_operator(char symbol, const int *arity, int *type, int *priority,
                const int *operator_counter, int *error) {
    int res = 0;
    if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' ||
        symbol == '^') {
        res = 1;
        if (*operator_counter == 0 && *arity == 1) {
            *type = 1;
            switch (symbol) {
                case '-':
                    *priority = 1;
                    break;
                case '+':
                    *priority = 1;
                    break;
                case '*':
                    *priority = 2;
                    break;
                case '/':
                    *priority = 2;
                    break;
                case '^':
                    *priority = 3;
                    break;
            }
        } else if (*operator_counter == 0 && *arity == 0) {
            if (symbol == '-') {
                *type = 2;
                *priority = 5;
            } else {
                *error = OPERATOR_ERROR;
            }
        } else if (*operator_counter == 1) {
            if (symbol == '-') {
                *type = 2;
                *priority = 5;
            } else {
                *error = OPERATOR_ERROR;
            }
        } else if (*operator_counter > 1) {
            *error = OPERATOR_ERROR;
        }
    } else {
        res = 0;
    }
    return res;
}

int is_bracket(char symbol, int *type, int *priority, int *open_brackets,
               int *close_brackets, int *error) {
    int res = 0;
    *priority = -1;
    if (symbol == '(') {
        res = 1;
        *type = 4;
        (*open_brackets)++;
    } else if (symbol == ')') {
        res = 1;
        *type = 5;
        (*close_brackets)++;
    }
    if (*close_brackets > *open_brackets) *error = BRACKETS_ERROR;
    return res;
}

int is_function(char first_symbol, char second_symbol, int *fun_len, int *type,
                int *priority) {
    int res = 0;
    *type = 3;
    *priority = 4;
    if (first_symbol == 's' && second_symbol == 'i') {
        res = 1;
        *fun_len = 3;
    } else if (first_symbol == 'c' && second_symbol == 'o') {
        res = 1;
        *fun_len = 3;
    } else if (first_symbol == 't' && second_symbol == 'a') {
        res = 1;
        *fun_len = 3;
    } else if (first_symbol == 'c' && second_symbol == 't') {
        res = 1;
        *fun_len = 3;
    } else if (first_symbol == 's' && second_symbol == 'q') {
        res = 1;
        *fun_len = 4;
    } else if (first_symbol == 'l' && second_symbol == 'n') {
        res = 1;
        *fun_len = 2;
    }
    return res;
}

int is_variable(char symbol, int *type, int *priority) {
    int res = 0;
    if (symbol == 'x') {
        res = 1;
        *priority = -1;
        *type = 7;
    }
    return res;
}
