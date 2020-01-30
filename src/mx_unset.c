#include "ush.h"

int mx_unset(char **split) {
    int result = 0;
    
    if (split == NULL) {
        fprintf(stderr, "unset: not enough arguments\n");
        return 1;
    }
    for (int i = 0; split[i]; i++) {
        if (unsetenv(split[i]) == -1) {
            fprintf(stderr, "unset: %s: invalid parameter name\n", split[i]);
            result = 1;
        }
    }
    return result;
}
