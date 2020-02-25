#include "ush.h"

static int check_argument(char **args) {
    if (!args[0]) {
        fprintf(stderr, "usage: color [1234567]\n");
        return 1;
    }
    if (mx_arr_size(args) > 1) {
        fprintf(stderr, "color: too many arguments\n");
        return 1;
    }
    if (strlen(args[0]) > 1 || !isnumber(args[0][0])) {
        fprintf(stderr, "color: invalid argument: %s\n", args[0]);
        return 1;
    }
    return 0;
}

int mx_color(char **args) {
    int color = 0;

    if (check_argument(args))
        return 1;
    color = args[0][0] - '0';
    if (color > 7 || color < 0) {
        fprintf(stderr, "color: no such color [%d]\n", color);
        return 1;
    }
    mx_print_color(color);
    return 0;
}

void mx_print_color(int color) {
    static int st_color = -1;

    if (color != -1) {
        printf("\x1b[0;3%dm", color);
        st_color = color;
    }
    else if (st_color != -1) {
        printf("\x1b[0;3%dm", st_color);
    }
    else {
        printf("\x1b[0m");
    }
}

