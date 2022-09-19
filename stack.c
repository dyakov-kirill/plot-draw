#include "stack.h"

#include <stdlib.h>

#include "parser.h"

t_stack *init_stack(t_token *data) {
    t_stack *res = (t_stack *)malloc(sizeof(t_stack));
    res->data = data;
    return res;
}

void push_stack(t_stack **stack, t_token *data) {
    t_stack *elem = (t_stack *)malloc(sizeof(t_stack));
    elem->data = data;
    elem->next = *stack;
    *stack = elem;
}

t_token *pop_stack(t_stack **stack) {
    t_token *res = (*stack)->data;
    t_stack *tmp = *stack;
    (*stack) = (*stack)->next;
    free(tmp);

    return res;
}

void destroy_stack(t_stack *stack) {
    while (stack->next != NULL) {
        pop_stack(&stack);
    }
    pop_stack(&stack);
}
