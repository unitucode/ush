#include "ush.h"

static char *get_saved_path(char **env, char **var_name) {
    char *saved_path = NULL;

    for (int i = 0; env[i]; i++) {
        mx_get_name(env[i], var_name);
        if (!strcmp((*var_name), "PATH"))
            saved_path = mx_get_var_info(env[i], 1);
        if (saved_path)
            break;
    }
    return saved_path;
}

void mx_env_parse_vars(char **argv, char **path, int *idx, char **env) {
    char *var_name = NULL;
    char *saved_path = get_saved_path(env, &var_name);

    for (; argv[*idx]; (*idx)++) {
        if (mx_match(argv[*idx], MX_ENV_VAR)) {
            mx_get_name(argv[*idx], &var_name);
            mx_putenv(argv[*idx]);
            if (!strcmp(var_name, "PATH") && !(*path))
                *path = strdup(getenv("PATH"));
        }
        else
            break;
    }
    if (!(*path))
        *path = strdup(saved_path);
    mx_strdel(&saved_path);
    mx_strdel(&var_name);
}
