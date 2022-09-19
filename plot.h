#ifndef SRC_PLOT_H_
#define SRC_PLOT_H_
#include <math.h>

#include "parser.h"
#include "token.h"

#define ROWS 25
#define COLUMNS 80

#define DELTA_X (4. * M_PI) / 79.
#define DELTA_Y 2. / 24.

#define X_BOUND 4. * M_PI + 1e-6
#define Y_BOUND 2

void draw_plot(char **plot, int n, int m);
char **get_plot(t_token **expr, int n, char **graph);
char **init_plot(int n, int m);
void free_plot(char **plot);

#endif  // SRC_PLOT_H_
