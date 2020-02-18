#include "ush.h"

int mx_print_env_error(char option, char *err_arg, int error) {
    if (error == 2)
        fprintf(stderr, "env: unsetenv %s: Invalid argument\n", err_arg);
    else {
        if (error == 0)
            fprintf(stderr, "env: illegal option -- %c\n", option);
        if (error == 1)
            fprintf(stderr,
                    "env: option requires an argument -- %c\n", option);
        fprintf(stderr,
                "usage: env [-i] [-P utilpath] [-u name]\n");
        fprintf(stderr,
                "           [name=value ...] [utility [argument ...]]\n");
    }
    return 1;
}
