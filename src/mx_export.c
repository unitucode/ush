#include "ush.h"

static char *get_var_name(char *str);
static char *get_var_val(char *arg);

int mx_export(char **args) {
    if (args[0] == NULL)
        mx_print_env();
    else {
        for (int i = 0; args[i]; i++) {
            if (mx_match(args[i], MX_EXPORT_ARG))
                if (mx_match(args[i], MX_ENV_ARG)) {
                    setenv(get_var_name(args[i]), get_var_val(args[i]), 1);
                    // And add this Variable to own export list
                }
                else
                    printf("ONLY FOR EXPORT\n"); // Add only to own export list
            else
                printf("ERROR: %s\n", args[i]); // Pars Errors!
        }
    }
    return 0;
}

static char *get_var_name(char *arg) {
    char *name = mx_strndup(arg, mx_get_char_index(arg, '='));

    return name;
}

static char *get_var_val(char *arg) {
    char *value = mx_strdup(arg + mx_get_char_index(arg, '=') + 1);

    return value;
}
