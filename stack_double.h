#ifndef SRC_STACK_DOUBLE_H_
#define SRC_STACK_DOUBLE_H_
#include "parser.h"
#include "token.h"

typedef struct s_stack_d t_stack_d;

typedef struct s_stack_d {
    double data;
    t_stack_d *next;
} t_stack_d;

t_stack_d *init_stack_d(double data);
void push_stack_d(t_stack_d **stack, double data);
double pop_stack_d(t_stack_d **stack);

#endif  // SRC_STACK_DOUBLE_H_
