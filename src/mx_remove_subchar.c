#include "ush.h"

bool mx_remove_subchar(char *substitution) {
    unsigned int len = strlen(substitution);

    if (substitution[0] == '`' && substitution[len - 1] == '`') {
        substitution[len - 1] = '\0';
        memmove(substitution, substitution + 1, len - 1);
        return true;
    }
    if (substitution[0] == '$' && substitution[1] == '('
        && substitution[len - 1] == ')') {
        substitution[len - 1] = '\0';
        memmove(substitution, substitution + 2, len - 2);
        return false;
    }
    return true;
}

// static char *replace_arg_quotes(char *arg) {
//     unsigned int len = strlen(arg);

//     if (arg[len - 1] == '\"' && !mx_isescape_char(arg, len - 1)) {
//         arg[len - 1] = '\0';
//     }
//     if (arg[0] == '\"' && !mx_isescape_char(arg, 0)) {
//         memmove(arg, arg + 1, len - 1);
//     }
//     return arg;
// }
