#include "ush.h"

static char *get_var_name(char *str);
static char *get_var_val(char *arg);
static bool parse_error(char *arg);

int mx_export(char **args)
{
    bool args_stop = 0;

    if (args[0] == NULL) // MAYBE BUG WHEN "-" flag
        mx_print_env();
    else
        for (int i = 0; args[i] && !args_stop; i++)
            if (mx_match(args[i], MX_EXPORT_ARG))
                if (mx_match(args[i], "="))
                {
                    setenv(get_var_name(args[i]), get_var_val(args[i]), 1);
                    // And add this Variable to own export list
                }
                else
                    printf("ONLY FOR EXPORT\n"); // Add only to export list
            else
                args_stop = parse_error(args[i]);
    return 0;
}

static bool parse_error(char *arg)
{
    if (mx_match(arg, "^[-+]"))
        fprintf(stderr, "export: does not accept any options: %c%c\n",
                arg[0], arg[1]);
    else if (mx_match(arg, "^[0-9]"))
        fprintf(stderr, "export: not an identifier: %s\n",
                get_var_name(arg));
    else
        fprintf(stderr, "export: not valid in this context: %s\n",
                get_var_name(arg));
    return 1;
}

static char *get_var_name(char *arg)
{
    char *name = mx_strndup(arg, mx_get_char_index(arg, '='));

    return name;
}

static char *get_var_val(char *arg)
{
    char *value = mx_strdup(arg + mx_get_char_index(arg, '=') + 1);

    return value;
}
