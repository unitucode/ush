#include "ush.h"

static char *get_formated_arg(char *str);

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
    if (!strlen(command))
        return NULL;
    arguments = mx_split_command(command);
    len = mx_list_size(arguments);
    result = malloc(sizeof(char *) * (len + 1));
    result[len] = NULL;
    for (t_list *cur = arguments; cur; cur = cur->next) {
        result[i++] = get_formated_arg(cur->data);
    }
    mx_del_list(&arguments);
    mx_strdel(&command);
    return result;
}

static char *get_formated_arg(char *str) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int len = strlen(str);
    unsigned int index = 0;
    bool is_quotes = false;

    for (unsigned int i = 0; i < len; i++) {
        if ((str[i] == MX_S_QUOTES || str[i] == MX_D_QUOTES) && !mx_isescape_char(str, i)) {
            is_quotes = !is_quotes;
            i++;
        }
        if (mx_isescape_char(str, i) && !is_quotes) {
            i++;
        }
        result[index++] = str[i];
    }
    return result;
}
