#include "ush.h"

char **mx_interpretate(char *command, int *code) {
    t_list *arguments = NULL;
    char **result = NULL;
    unsigned int i = 0;
    int len = 0;

    if (!(command = mx_replace_env(command, code))) {
        fprintf(stderr, "%s: bad substitution\n", MX_SHELL_NAME);
        return NULL; // arg for one command;
    }
    command = mx_replace_tilde(command);
    if (!(command = mx_replace_substitution(command, code))) {
        fprintf(stderr, "%s: unmatched quote\n", MX_SHELL_NAME);
        return NULL;
    }
    arguments = mx_split_command(command);
    len = mx_list_size(arguments);
    result = malloc(sizeof(char *) * (len + 1));
    result[len] = NULL;
    for (t_list *cur = arguments; cur; cur = cur->next) {
        result[i++] = strdup(cur->data);
    }
    mx_del_list(&arguments);
    mx_strdel(&command);
    return result;
}
