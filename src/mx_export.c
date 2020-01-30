#include "ush.h"

static char *get_var_info(char *arg, bool info_type);
static bool parse_error(char *arg, char *arg_name);

int mx_export(char **args) {
    bool args_stop = 0;

    if (args[0] == NULL) // MAYBE BUG WHEN "-" flag
        mx_print_env();
    else
        for (int i = 0; args[i] && !args_stop; i++) {
            char *name = get_var_info(args[i], 0);
            char *val = get_var_info(args[i], 1);

            if (mx_match(args[i], MX_EXPORT_ARG)) {
                if (mx_match(args[i], "="))
                    setenv(name, val, 1);
                printf("ONLY FOR EXPORT\n"); // Add to own export list
            }
            else
                args_stop = parse_error(args[i], name);
            mx_strdel(&name);
            mx_strdel(&val);
        }
    return 0;
}

static bool parse_error(char *arg, char *arg_name) {
    if (mx_match(arg, "^[-+]"))
        fprintf(stderr, "export: does not accept any options: %c%c\n",
                arg[0], arg[1]);
    else if (mx_match(arg, "^[0-9]"))
        fprintf(stderr, "export: not an identifier: %s\n", arg_name);
    else
        fprintf(stderr, "export: not valid in this context: %s\n", arg_name);
    return 1;
}

// argument 'info_type' inform what func need to return (0-name/1-val)
static char *get_var_info(char *arg, bool info_type) {
    char *info = NULL;

    if (info_type == 0)
        info = mx_strndup(arg, mx_get_char_index(arg, '='));
    else
        info = mx_strdup(arg + mx_get_char_index(arg, '=') + 1);
    return info;
}
