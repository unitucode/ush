#include "ush.h"

int mx_set(char **argv, int fd) {
    if (argv[0] != NULL) {
        fprintf(stderr, "set: command does not accept any options\n");
        return 1;
    }
    mx_print_var_list(SHELL, fd);
    return 0;
}
