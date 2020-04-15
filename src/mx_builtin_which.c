#include "ush.h"

bool mx_builtin_which(char *file, int *mode) {
    if (mx_is_builtin(file)) {
        if (*mode != 2)
            dprintf(0, "%s: shell built-in comand\n", file);
        if (*mode != 1)
            *mode = 2;
        return 0;
    }
    return 1;
}
