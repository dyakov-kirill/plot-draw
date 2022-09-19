#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_
#include <stdlib.h>

#include "token.h"

void free_empty_array(t_token ***ar);
void free_ptr_array(t_token ***ar, int n);
void free_char_array(char ***ar, int n);

t_token **copy_array(t_token **ar, int n);

#endif  // SRC_UTILS_H_
