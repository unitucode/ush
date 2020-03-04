#include "ush.h"

char *mx_clear_slash_end(char *str) {
    if (str[mx_strlen(str) - 1] == '/') {
        char *result = mx_strndup(str, mx_strlen(str) - 1);

        mx_strdel(&str);
        return result;
    }
    else
        return str;
}
