#include "ush.h"

// argument 'info_type' inform what func need to return (0-name/1-val)
char *mx_get_var_info(char *arg, bool info_type) {
    char *info = NULL;

    if (info_type == 0)
        info = mx_strndup(arg, mx_get_char_index(arg, '='));
    else
        info = mx_strdup(arg + mx_get_char_index(arg, '=') + 1);
    return info;
}
