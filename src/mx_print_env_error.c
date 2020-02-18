#include "ush.h"

int mx_print_env_error(char option, bool error) {
    if (error == 0)
        fprintf(stderr, "env: illegal option -- %c\n", option);
    if (error == 1)
        fprintf(stderr, "env: option requires an argument -- %c\n", option);
    fprintf(stderr, "usage: env [-i] [-P utilpath] [-u name]\n");
    fprintf(stderr, "           [name=value ...] [utility [argument ...]]\n");
    return 1;
}
