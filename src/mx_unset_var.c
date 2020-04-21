#include "ush.h"

int mx_unset_var(char *var) {
    int result = 0;

    result = unsetenv(var);
    if (result != -1 && mx_match(var, MX_UNSET_ARG)) {
        mx_var_list_delete(SHELL, var);
        mx_var_list_delete(EXP, var);
    }
    else
        result = -1;
    return result;
}
