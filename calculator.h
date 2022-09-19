#ifndef SRC_CALCULATOR_H_
#define SRC_CALCULATOR_H_

#include <stdlib.h>

#include "calculator.h"
#include "parser.h"
#include "stack_double.h"
#include "translator.h"

double get_value_with_x(t_token **expr, int tokens_num, double x_value);
double get_expression_value(t_token **expr, int tokens_num);
void make_operation(t_token *expr, t_stack_d **stack);

double t_sum(t_stack_d **stack);
double t_diff(t_stack_d **stack);
double t_multiple(t_stack_d **stack);
double t_div(t_stack_d **stack);
double t_pow(t_stack_d **stack);
double t_sin(t_stack_d **stack);
double t_cos(t_stack_d **stack);
double t_tan(t_stack_d **stack);
double t_ctg(t_stack_d **stack);
double t_sqrt(t_stack_d **stack);
double t_ln(t_stack_d **stack);
double t_neg(t_stack_d **stack);

#endif  // SRC_CALCULATOR_H_
