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

static int parse_flags(char **flags, int *idx, int *mode) {
    for (*idx = 0; flags[*idx] && flags[*idx][0] == '-'
         && strcmp(flags[*idx], "--") != 0;) {
        if (!mx_match(flags[*idx], "^-[ea]+$")) {
            fprintf(stderr, "unset: invalid option\n");
            fprintf(stderr, "usage: unset [-ea] var ...\n");
            return 1;
        }
        if (mx_match(flags[*idx], "a"))
            *mode = 2;
        *mode = *mode == 2 ? 2 : 1;
        (*idx)++;
    }
    if (flags[*idx] && !strcmp(flags[*idx], "--"))
        (*idx)++;
    return 0;
}

int mx_unset(char **args) {
    int result = 0;
    int idx;
    int mode = 0;

    result = parse_flags(args, &idx, &mode);
    for (; args[idx] && result != 1; idx++) {
        if (unset_var(args[idx]) == -1 && !result) {
            fprintf(stderr, "unset: %s: invalid parameter name\n", args[idx]);
            result = 1;
        }
    }
    if (mode && result != 1) {
        if (mode == 2)
            unset_all();
        mx_clearenv();
    }
    return result;
}
