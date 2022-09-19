#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calculator.h"
#include "parser.h"
#include "plot.h"
#include "stack.h"
#include "stack_double.h"
#include "token.h"
#include "translator.h"
#include "utils.h"

int main() {
    int error_code = -1;
    char *expr = get_string();
    int n = 0;
    t_token **ar = string_to_tokens(expr, &n, &error_code);
    if (error_code == -1) {
        int flag = 0;
        t_token **rpn = get_polish_notation((const t_token **)ar, n, &flag);
        init_numbers(rpn, n - get_brackets_num(expr));
        char **plot = init_plot(ROWS, COLUMNS);
        plot = get_plot(rpn, n - get_brackets_num(expr), plot);
        draw_plot(plot, ROWS, COLUMNS);
        free_empty_array(&rpn);
        free_char_array(&plot, ROWS);
    } else if (error_code == 0) {
        printf("NUMBER_ERROR");
    } else if (error_code == 1) {
        printf("OPERATOR_ERROR");
    } else if (error_code == 3) {
        printf("FUNCTION_ERROR");
    } else if (error_code == 5) {
        printf("INCORRECT_SYMBOLS");
    } else if (error_code == 7) {
        printf("VARIABLE_ERROR");
    } else if (error_code == 4) {
        printf("BRACKET_ERROR");
    }
    for (int i = 0; i <= n; i++) {
        free(ar[i]);
    }
    free(ar);
    free(expr);
    return 0;
}
