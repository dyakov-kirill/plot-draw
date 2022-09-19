#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#define NUMBER_ERROR 0
#define OPERATOR_ERROR 1
#define FUNCTION_ERROR 3
#define BRACKETS_ERROR 4
#define INCORRECT_SYMBOLS 5
#define VARIABLE_ERROR 7

#include "token.h"

char *get_string();  // возвращает массив символов без пробелов (если они былм)
// t_token get_next_token(char *string, int (*is_function) (char *));
t_token **string_to_tokens(
    char *string, int *array_size,
    int *error);  // преобразует строку в массив указателей на токены
t_token *create_token(char *value, int type,
                      int priority);  // создаёт новый токен с данным значением,
                                      // типом и приоритетом
t_token **add_number(t_token **token_array, int *array_size, char *string,
                     int *i, int *arity, int *type, int *priority,
                     int *operator_counter, int *error,
                     int *num_counter);  //  добавляет число в массив токенов
t_token **add_operator(t_token **token_array, int *array_size,
                       const char *string, int i, int *type, int *priority,
                       int *operator_counter,
                       int *error);  //  добавляет оператор в массив токенов
t_token **add_bracket(
    t_token **token_array, int *array_size, const char *string, int i,
    int *type, int *priority);  //  добавляет скобки в массив токенов
t_token **add_function(t_token **token_array, int *array_size,
                       const char *string, int *i, int *type, int *priority,
                       int *operator_counter, const int *fun_len,
                       int *error);  // добавляет функцию в массив токенов
t_token **add_variable(t_token **token_array, int *array_size, char *string,
                       int i, int *arity, int *type, int *priority,
                       int *operator_counter,
                       int *error);  // добавляет переменную  в массив токенов
int is_operator(char symbol, const int *arity, int *type, int *priority,
                const int *operator_counter, int *error);
int is_number(char symbol, int *type, int *priority);
int is_function(char first_symbol, char second_symbol, int *fun_len, int *type,
                int *priority);
int is_bracket(char symbol, int *type, int *priority, int *open_brackets,
               int *close_brackets, int *error);
int is_variable(char symbol, int *type, int *priority);

#endif  // SRC_PARSER_H_
