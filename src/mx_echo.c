#include "ush.h"

static unsigned int set_flags(bool *is_nl, bool *is_e, char **argv) {
    unsigned int index = 0;

    while (argv[index]) {
        if (mx_match(argv[index], "^-[nEe]+$")) {
            for (unsigned int i = 0; i < strlen(argv[index]); i++) {
                if (argv[index][i] == 'E')
                    *is_e = false;
                if (argv[index][i] == 'e')
                    *is_e = true;
                if (argv[index][i] == 'n')
                    *is_nl = false;
            }
        }
        else
            break;
        index++;
    }
    return index;
}

static char *replace_octal(char *arg) {
    char *result = mx_strnew(strlen(arg));
    int index = 0;
    int num_size = 0;
    char *octal_num = NULL;
    char *save = arg;

    while ((index = mx_get_substr_index(arg, "\\0")) >= 0) {
        strncat(result, arg, index);
        while (arg[++index] >= '0' && arg[index] <= '7' && arg[index])
            num_size++;
        octal_num = strndup(arg + index - num_size, num_size);
        result[strlen(result)] = (char)strtol(octal_num, NULL, 8);
        mx_strdel(&octal_num);
        arg += index;
        num_size = 0;
    }
    strcat(result, arg);
    mx_strdel(&save);
    return result;
}

static char *replace_escape(char *arg, bool *is_nl) {
    int index = 0;
    char *result = mx_strnew(ARG_MAX);

    if ((index = mx_get_substr_index(arg, "\\c")) >= 0) {
        strncpy(result, arg, index);
        *is_nl = false;
    }
    else
        strcpy(result, arg);
    result = mx_replace_escape(result, "\\a", '\x07', true);
    result = mx_replace_escape(result, "\\b", '\x08', true);
    result = mx_replace_escape(result, "\\f", '\x0c', true);
    result = mx_replace_escape(result, "\\n", '\x0a', true);
    result = mx_replace_escape(result, "\\r", '\x0d', true);
    result = mx_replace_escape(result, "\\t", '\x09', true);
    result = mx_replace_escape(result, "\\v", '\x0b', true);
    result = mx_replace_escape(result, "\\\\", '\\', true);
    result = replace_octal(result);
    return result;
}

int mx_echo(char **args, int fd) {
    bool is_nl = true;
    bool is_e = false;
    unsigned int index = 0;
    char *output = NULL;

    index = set_flags(&is_nl, &is_e, args);
    while (args[index]) {
        if (is_e)
            output = replace_escape(args[index], &is_nl);
        else
            output = strdup(args[index]);
        dprintf(fd, "%s", output);
        mx_strdel(&output);
        index++;
        if (args[index])
            dprintf(fd, " ");
    }
    if (is_nl)
        dprintf(fd, "\n");
    return 0;
}
