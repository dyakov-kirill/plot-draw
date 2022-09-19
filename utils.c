#include "utils.h"

#include <stdio.h>
#include <string.h>

void free_empty_array(t_token ***ar) { free(*ar); }

void free_char_array(char ***ar, int n) {
    for (int i = 0; i < n; i++) {
        free((*ar)[i]);
    }
    free(*ar);
}
