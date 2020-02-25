#include "ush.h"

static int unset_var(char *var) {
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

static void unset_all(void) {
    t_list **shell = mx_get_var_list(SHELL);
    t_list *curr = *shell;
    char *var = NULL;

    while (curr) {
        mx_get_name(curr->data, &var);
        mx_var_list_delete(EXP, var);
        curr = curr->next;
    }
    if (var)
        mx_strdel(&var);
}

static int unset_parse_flag(char *flag) {
    if (!mx_match(flag, "^-[ea]+")) {
        fprintf(stderr, "unset: invalid option\n");
        fprintf(stderr, "usage: unset [-ea] var ...\n");
        return 1;
    }
    if (mx_match(flag, "a"))
        unset_all();
    mx_clearenv();
    return 0;
}

int mx_unset(char **args) {
    int result = 0;

    for (int i = 0; args[i]; i++) {
        if (args[i][0] == '-')
            result = unset_parse_flag(args[i]);
        else if (unset_var(args[i]) == -1 && !result) {
            fprintf(stderr, "unset: %s: invalid parameter name\n", args[i]);
            result = 1;
        }
    }
    return result;
}
