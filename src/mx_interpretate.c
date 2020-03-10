#include "ush.h"

static char *format_quotes(char *str) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int len = strlen(str);
    unsigned int index = 0;
    bool is_quotes[2] = {false, false};

    for (unsigned int i = 0; i < len; i++) {
        if ((str[i] == '\'') && !mx_isescape_char(str, i) && !is_quotes[1])
            is_quotes[0] = !is_quotes[0];
        if ((str[i] == '\"') && !mx_isescape_char(str, i) && !is_quotes[0])
            is_quotes[1] = !is_quotes[1];
        if (is_quotes[1] && !is_quotes[0] && mx_isescape_char(str, i + 1)
            && (str[i + 1] == '$' || str[i + 1] == '\\')) {
            i++;
        }
        result[index++] = str[i];
    }
    mx_strdel(&str);
    return result;
}

static char *get_formated_arg(char *str) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int len = strlen(str);
    unsigned int index = 0;
    bool is_quotes[2] = {false, false};

    for (unsigned int i = 0; i < len; i++) {
        if ((str[i] == '\'') && !mx_isescape_char(str, i) && !is_quotes[1]) {
            is_quotes[0] = !is_quotes[0];
            continue;
        }
        if ((str[i] == '\"') && !mx_isescape_char(str, i) && !is_quotes[0]) {
            is_quotes[1] = !is_quotes[1];
            continue;
        }
        if (mx_isescape_char(str, i + 1) && !is_quotes[0] && !is_quotes[1])
            i++;
        result[index++] = str[i];
    }
    return result;
}

static char **get_result(char *command) {
    char **result = NULL;
    t_list *arguments = NULL;
    int len = 0;
    unsigned int i = 0;

    arguments = mx_split_command(command);
    len = mx_list_size(arguments);
    result = malloc(sizeof(char*) * (len + 1));
    result[len] = NULL;
    for (t_list *cur = arguments; cur; cur = cur->next) {
        cur->data = format_quotes(cur->data);
        result[i++] = get_formated_arg(cur->data);
    }
    mx_del_list(&arguments);
    mx_strdel(&command);
    return result;
}

char **mx_interpretate(char *command, int *code) {
    if (!(command = mx_replace_env(command, code))) {
        fprintf(stderr, "%s: bad substitution\n", MX_SHELL_NAME);
        return NULL;
    }
    command = mx_replace_tilde(command);
    if (!(command = mx_replace_substitution(command, code))) {
        fprintf(stderr, "%s: unmatched quote\n", MX_SHELL_NAME);
        return NULL;
    }
    if (!strlen(command)) {
        mx_strdel(&command);
        return NULL;
    }
    return get_result(command);
}
