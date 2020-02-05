#include "ush.h"

char *mx_clear_slashes_end(char *str) {
    int length = mx_strlen(str);
    int slashes = 0;
    char *result;

    for (int i = length - 1; i > 0 && str[i] == '/'; i--)
        slashes++;
    result = mx_strnew(length - slashes);
    result = mx_strncpy(result, str, length - slashes);
    return result;
}
