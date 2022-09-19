#ifndef SRC_TOKEN_H_
#define SRC_TOKEN_H_

typedef enum {
    NUMBER,
    B_OPERATOR,
    U_OPERATOR,
    FUNCTION,
    O_BRACKET,
    C_BRACKET,
    T_NULL,
    VARIABLE
} token_type;

typedef struct s_token {
    char value[10];
    token_type type;
    int priority;
    double num;
} t_token;

int get_priority(t_token *t);
token_type get_type(t_token *t);
int get_brackets_num(const char *expr);
void init_numbers(t_token **tokens, int num);

#endif  // SRC_TOKEN_H_
