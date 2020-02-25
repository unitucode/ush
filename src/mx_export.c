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
    mx_strdel(&arg_name);
    return 1;
}

static void add_var_to_lists(char *arg) {
    mx_var_list_insert(SHELL, arg);
    mx_var_list_insert(EXP, arg);
    mx_strdel(&arg);
}

static void export_var_to_lists(char *arg) {
    t_list **shell_list = mx_get_var_list(SHELL);
    t_list *current = *shell_list;
    char *arg_name = NULL;
    char *var_name = NULL;

    mx_get_name(arg, &arg_name);
    while (current) {
        mx_get_name(current->data, &var_name);
        if (strcmp(arg_name, var_name) == 0) {
            mx_var_list_insert(EXP, current->data);
            mx_putenv(current->data);
            break ;
        }
        current = current->next;
        if (current)
            mx_get_name(current->data, &var_name);
    }
    if (!current)
        add_var_to_lists(mx_strjoin(arg, "="));
    mx_delete_names(&var_name, &arg_name, NULL);
}


int mx_export(char **args, int fd) {
    bool args_stop = 0;

    if (args[0] == NULL)
        mx_print_var_list(EXP, fd);
    else
        for (int i = 0; args[i] && !args_stop; i++)
            if (mx_match(args[i], MX_EXPORT_ARG))
                if (!mx_match(args[i], "="))
                    export_var_to_lists(args[i]);
                else {
                    mx_putenv(args[i]);
                    add_var_to_lists(strdup(args[i]));
                }
            else
                args_stop = parse_error(args[i]);
    return 0;
}
