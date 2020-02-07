#include "ush.h"

static int unset_all(char *var) {
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

int mx_unset(char **args) {
    int result = 0;

    if (args == NULL) {
        fprintf(stderr, "unset: not enough arguments\n");
        return 1;
    }
    for (int i = 0; args[i]; i++)
        if (unset_all(args[i]) == -1 && !result) {
            fprintf(stderr, "unset: %s: invalid parameter name\n", args[i]);
            result = 1;
        }
    return result;
}
