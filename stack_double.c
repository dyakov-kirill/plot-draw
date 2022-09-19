#include "stack_double.h"

#include <stdlib.h>

#include "parser.h"

t_stack_d *init_stack_d(double data) {
    t_stack_d *res = (t_stack_d *)malloc(sizeof(t_stack_d));
    res->data = data;
    return res;
}

void push_stack_d(t_stack_d **stack, double data) {
    t_stack_d *elem = (t_stack_d *)malloc(sizeof(t_stack_d));
    elem->data = data;
    elem->next = *stack;
    *stack = elem;
}

double pop_stack_d(t_stack_d **stack) {
    double res = (*stack)->data;
    t_stack_d *tmp = *stack;
    (*stack) = (*stack)->next;
    free(tmp);

    return res;
}
