#include "ush.h"

int mx_unset(char *name) {
    int result = 0;
    char **split;
    
    if (mx_strcmp("", name) == 0) {
        fprintf(stderr, "unset: not enough arguments\n");
        return 1;
    }
    split = mx_strsplit(name, ' ');
    for (int i = 0; split[i]; i++) {
        if (unsetenv(split[i]) == -1) {
            fprintf(stderr, "unset: %s: invalid parameter name\n", split[i]);
            result = 1;
        }
    }
    for (int i = 0; split[i]; i++) {
        mx_strdel(&split[i]);
    }
    free(split);
    split = NULL;
    return result;
}
