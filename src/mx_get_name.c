#include "ush.h"

void mx_get_name(char *var, char **name) {
    if (*name != NULL)
        mx_strdel(name);
    *name = strndup(var, mx_get_char_index(var, '='));
}
