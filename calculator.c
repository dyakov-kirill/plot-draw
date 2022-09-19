#include "calculator.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "stack_double.h"
#include "translator.h"

double get_value_with_x(t_token **expr, int tokens_num, double x_value) {
    for (int i = 0; i < tokens_num; i++) {
        if (expr[i]->type == VARIABLE) {
            expr[i]->num = x_value;
        }
    }
    double res = get_expression_value(expr, tokens_num);
    for (int i = 0; i < tokens_num; i++) {
        if (expr[i]->type == VARIABLE) {
            expr[i]->num = 0;
        }
    }
    return res;
}

double get_expression_value(t_token **expr, int tokens_num) {
    t_stack_d *stack = init_stack_d(0);
    for (int i = 0; i < tokens_num; i++) {
        if (get_type(expr[i]) == NUMBER || get_type(expr[i]) == VARIABLE) {
            push_stack_d(&stack, expr[i]->num);
        } else if (get_type(expr[i]) == B_OPERATOR ||
                   get_type(expr[i]) == FUNCTION) {
            make_operation(expr[i], &stack);
        } else if (get_type(expr[i]) == U_OPERATOR) {
            push_stack_d(&stack, t_neg(&stack));
        }
    }
    double r = stack->data;
    free(stack->next);
    free(stack);
    return -r;
}

void make_operation(t_token *expr, t_stack_d **stack) {
    if (strcmp(expr->value, "+") == 0) {
        push_stack_d(stack, t_sum(stack));
    } else if (strcmp(expr->value, "-") == 0) {
        push_stack_d(stack, t_diff(stack));
    } else if (strcmp(expr->value, "*") == 0) {
        push_stack_d(stack, t_multiple(stack));
    } else if (strcmp(expr->value, "/") == 0) {
        push_stack_d(stack, t_div(stack));
    } else if (strcmp(expr->value, "^") == 0) {
        push_stack_d(stack, t_pow(stack));
    } else if (strcmp(expr->value, "sin") == 0) {
        push_stack_d(stack, t_sin(stack));
    } else if (strcmp(expr->value, "cos") == 0) {
        push_stack_d(stack, t_cos(stack));
    } else if (strcmp(expr->value, "tan") == 0) {
        push_stack_d(stack, t_tan(stack));
    } else if (strcmp(expr->value, "ctg") == 0) {
        push_stack_d(stack, t_ctg(stack));
    } else if (strcmp(expr->value, "sqrt") == 0) {
        push_stack_d(stack, t_sqrt(stack));
    } else if (strcmp(expr->value, "ln") == 0) {
        push_stack_d(stack, t_ln(stack));
    }
}

double t_sum(t_stack_d **stack) {
    double t_1 = pop_stack_d(stack);
    double t_2 = pop_stack_d(stack);
    double res = t_1 + t_2;
    return res;
}

double t_diff(t_stack_d **stack) {
    double t_1 = pop_stack_d(stack);
    double t_2 = pop_stack_d(stack);
    double res = t_1 - t_2;
    return res;
}

double t_multiple(t_stack_d **stack) {
    double t_1 = pop_stack_d(stack);
    double t_2 = pop_stack_d(stack);
    double res = t_1 * t_2;
    return res;
}

double t_div(t_stack_d **stack) {
    double t_1 = pop_stack_d(stack);
    double t_2 = pop_stack_d(stack);
    double res = t_1 / t_2;
    return res;
}

double t_pow(t_stack_d **stack) {
    double t_1 = pop_stack_d(stack);
    double t_2 = pop_stack_d(stack);
    double res = pow(t_2, t_1);
    return res;
}

double t_sin(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = sin(t);
    return res;
}

double t_cos(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = cos(t);
    return res;
}

double t_tan(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = tan(t);
    return res;
}

double t_ctg(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = 1 / tan(t);
    return res;
}

double t_sqrt(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = sqrt(t);
    return res;
}

double t_ln(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = log(t);
    return res;
}

double t_neg(t_stack_d **stack) {
    double t = pop_stack_d(stack);
    double res = -t;
    return res;
}
