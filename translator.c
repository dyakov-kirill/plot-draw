#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "stack.h"

t_token **get_polish_notation(const t_token **expr, int tokens_num, int *res) {
    int flag = 0;
    int i = 0;
    int j = 0;
    t_token **result = malloc(tokens_num * sizeof(t_token));
    t_token *null_token = malloc(sizeof(t_token));
    null_token->type = T_NULL;
    strcpy(null_token->value, "NULL");
    t_stack *stack = init_stack(null_token);
    while (i != tokens_num && flag == 0) {
        t_token *cur_token = (t_token *)expr[i++];
        switch (get_type(cur_token)) {
            case NUMBER:
                result[j++] = cur_token;
                break;
            case VARIABLE:
                result[j++] = cur_token;
                break;
            case FUNCTION:
                push_stack(&stack, cur_token);
                break;
            case B_OPERATOR:
                while (get_type(stack->data) == B_OPERATOR &&
                       get_priority(stack->data) >= get_priority(cur_token)) {
                    result[j++] = pop_stack(&stack);
                }
                push_stack(&stack, cur_token);
                break;
            case U_OPERATOR:
                while (get_type(stack->data) == U_OPERATOR &&
                       get_priority(stack->data) <= get_priority(cur_token)) {
                    result[j++] = pop_stack(&stack);
                }
                push_stack(&stack, cur_token);
                break;
            case O_BRACKET:
                push_stack(&stack, cur_token);
                break;
            case C_BRACKET:
                if (get_type(stack->data) == T_NULL) {
                    flag = 1;
                }
                while (flag == 0 && stack->data->type != O_BRACKET) {
                    if (get_type(stack->data) != T_NULL) {
                        result[j++] = pop_stack(&stack);
                    } else {
                        flag = 1;
                    }
                }
                pop_stack(&stack);
                if (flag == 0 && get_type(stack->data) == FUNCTION) {
                    result[j++] = pop_stack(&stack);
                }
                break;
            default:
                break;
        }
    }
    while (flag == 0 && get_type(stack->data) != T_NULL) {
        if (get_type(stack->data) == O_BRACKET) {
            flag = 1;
        }
        if (flag == 0 && stack->data->type == B_OPERATOR) {
            result[j++] = pop_stack(&stack);
        } else if (flag == 0 && stack->data->type == U_OPERATOR) {
            result[j++] = pop_stack(&stack);
        }
    }
    destroy_stack(stack);
    free(null_token);
    *res = !flag;
    return result;
}
