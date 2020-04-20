#include "ush.h"

void mx_env_parse_vars(char **argv, char **path, int *idx) {
    char *var_name = NULL;
    bool path_replace = 0;

    for (; argv[*idx]; (*idx)++) {
        if (mx_match(argv[*idx], MX_ENV_VAR)) {
            mx_get_name(argv[*idx], &var_name);
            mx_putenv(argv[*idx]);
            if (!strcmp(var_name, "PATH") && (!(*path) || path_replace)) {
                path_replace = 1;
                if (*path)
                    mx_strdel(path);
                *path = mx_get_var_info(argv[*idx], 1);
            }
        }
        else
            break;
    }
    if (!(*path) && mx_get_var_val(SHELL, "PATH"))
        *path = strdup(mx_get_var_val(SHELL, "PATH"));
    mx_strdel(&var_name);
}
