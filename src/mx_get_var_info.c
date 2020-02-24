#include "ush.h"

char *mx_get_var_info(char *arg, bool info_type) {
    char *info = NULL;

    if (info_type == 0) {
        if (arg[0] == '=')
            info = strndup(arg, mx_get_char_index(&arg[1], '='));
        else
            info = strndup(arg, mx_get_char_index(arg, '='));
    }
    else
        info = strdup(arg + mx_get_char_index(arg, '=') + 1);
    return info;
}
