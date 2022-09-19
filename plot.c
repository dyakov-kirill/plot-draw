#include "plot.h"

#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "token.h"

char **init_plot(int n, int m) {
    char **graph = malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        graph[i] = malloc(m * sizeof(char));
    }
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 80; j++) {
            graph[i][j] = '.';
        }
    }
    return graph;
}

void draw_plot(char **plot, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%c", plot[i][j]);
        }
        if (i != n - 1) {
            printf("\n");
        }
    }
}

char **get_plot(t_token **expr, int n, char **graph) {
    int column = 0;
    for (double x = 0; x <= X_BOUND; x += DELTA_X) {
        double val = get_value_with_x(expr, n, x);
        if (fabs(val) <= 1) {
            int counter = 0;
            int row = 0;
            val += 1;
            double min_diff = 10000000;
            for (double y = 0; y <= Y_BOUND; y += DELTA_Y) {
                double diff = fabs(val - y);
                if (diff < min_diff) {
                    min_diff = diff;
                    row = counter;
                }
                counter++;
            }
            graph[row][column] = '*';
        }
        column++;
    }
    return graph;
}
