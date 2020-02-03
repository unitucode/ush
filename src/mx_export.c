#include "ush.h"

static bool parse_error(char *arg) {
    char *arg_name = mx_get_var_info(arg, 0);

    if (mx_match(arg, "^[-+]"))
        fprintf(stderr, "export: does not accept any options: %c%c\n",
                arg[0], arg[1]);
    else if (mx_match(arg, "^[0-9]"))
        fprintf(stderr, "export: not an identifier: %s\n", arg_name);
    else
        fprintf(stderr, "export: not valid in this context: %s\n", arg_name);
    return 1;
}

static void add_var_to_lists(char *arg) {
    mx_var_list_insert("shell", arg);
    mx_var_list_insert("exp", arg);
}

int mx_export(char **args) {
    bool args_stop = 0;

    if (args[0] == NULL) // MAYBE BUG WHEN "-" flag
        mx_print_var_list("exp");
    else
        for (int i = 0; args[i] && !args_stop; i++)
            if (mx_match(args[i], MX_EXPORT_ARG)) {
                if (mx_match(args[i], "="))
                    putenv(args[i]);
                add_var_to_lists(args[i]);
            }
            else
                args_stop = parse_error(args[i]);
    return 0;
}
