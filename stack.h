#ifndef SRC_STACK_H_
#define SRC_STACK_H_
#include "parser.h"
#include "token.h"

typedef struct s_stack t_stack;

typedef struct s_stack {
    t_token *data;
    t_stack *next;
} t_stack;

t_stack *init_stack(t_token *data);
void push_stack(t_stack **stack, t_token *data);
t_token *pop_stack(t_stack **stack);
void destroy_stack(t_stack *stack);

#endif  // SRC_STACK_H_
