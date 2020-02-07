#include "ush.h"

char **mx_make_null_index(char **split, int index) {
    mx_strdel(&split[index]);
    split[index] = strdup("null0");
    for (int i = index - 1; split[i] && i > -1; i--) {
        if (strcmp(split[i], "null0") != 0) {
            mx_strdel(&split[i]);
            split[i] = strdup("null0");
            break;
        }
    }
    return split;
}
