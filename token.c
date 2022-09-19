#include "token.h"

#include <stdio.h>
#include <stdlib.h>

int get_priority(t_token *t) { return t->priority; }

token_type get_type(t_token *t) { return t->type; }

void init_numbers(t_token **tokens, int num) {
    for (int i = 0; i < num; i++) {
        if (tokens[i]->type == NUMBER) {
            tokens[i]->num = strtod(tokens[i]->value, NULL);
        }
    }
}

int get_brackets_num(const char *expr) {
    int res = 0;
    int i = 0;
    while (expr[i] != '\0') {
        if (expr[i] == '(' || expr[i] == ')') {
            res++;
        }
        i++;
    }
    return res;
}
