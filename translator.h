#ifndef SRC_TRANSLATOR_H_
#define SRC_TRANSLATOR_H_
#include "stack.h"
#include "token.h"

/*  В модуле translator будем переводить массив токенов
    в обратную польскую запись с помощью алгоритма Дейкстры */

t_token **get_polish_notation(
    const t_token **expr, int tokens_num,
    int *res);  // Переводит массив токенов в инфиксной записи в массив токенов
                // в обратной польской записи

#endif  // SRC_TRANSLATOR_H_
