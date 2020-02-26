#include "ush.h"

char **mx_exec_copy_argv(char **argv) {
    size_t size = mx_arr_size(argv);
    char **copy = malloc(sizeof(char*) * (size + 1));

    copy[size] = NULL;
    for (unsigned int i = 0; i < size; i++) {
        copy[i] = strdup(argv[i]);
    }
    return copy;
}
