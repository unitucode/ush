#include "ush.h"

static t_list *split_arguments(char *command);
static void skip_quotes(char *command, unsigned int *i);
static void skip_grave(char *command, unsigned int *i);
static char **replace_all(t_list *arguments);

char **mx_interpretate(char *command) {
    t_list *tmp_arguments = split_arguments(command);
    char **arguments = replace_all(tmp_arguments);

    mx_del_list(&tmp_arguments);
    return arguments;
}

static char **replace_all(t_list *arguments) {
    int size = mx_list_size(arguments);
    char **result = malloc(sizeof(char *) * (size + 1));
    int i = 0;

    result[size] = NULL;
    while (i < size) {
        result[i] = mx_replace_special(arguments->data);
        arguments = arguments->next;
        i++;
    }
    return result;
}

static t_list *split_arguments(char *command) {
    t_list *arguments = NULL;
    unsigned int len = 0;
    char *tmp = mx_strtrim(command);

    for (unsigned int i = 0; i < strlen(tmp); i++) {
        skip_grave(tmp, &i);
        skip_quotes(tmp, &i);
        if ((isspace(tmp[i]) 
            && !isspace(tmp[i + 1]) 
            && !mx_isescape_char(tmp, i))
            || !tmp[i + 1]) {
            if (!tmp[i + 1])
                i++;
            mx_push_back(&arguments, strndup(tmp + len, i - len));
            len = i;
        }
    }
    mx_strdel(&tmp);
    return arguments;
}

static void skip_quotes(char *command, unsigned int *i) {
    if (command[*i] == MX_D_QUOTES && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == MX_D_QUOTES
                && !mx_isescape_char(command, *i)) {
                break;
            }
            (*i)++;
        }
    }
}

static void skip_grave(char *command, unsigned int *i) {
    if (command[*i] == MX_GRAVE_ACCENT && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == MX_GRAVE_ACCENT
                && !mx_isescape_char(command, *i)) {
                break;
            }
            (*i)++;
        }
    }
}
