#include "ush.h"

static char *replace_escape(char *arg);
static unsigned int set_flags(bool *is_nl, bool *is_e, char **argv);
static void copy(char *result, char *replace);
static void print_nl(bool is_nl);

int mx_echo(char **args) {
    bool is_nl = true;
    bool is_e = true;
    unsigned int index = 0;
    char *output = NULL;

    index = set_flags(&is_nl, &is_e, args);
    while (args[index]) {
        if (is_e)
            output = replace_escape(args[index]);
        else
            output = strdup(args[index]);
        printf("%s", output);
        mx_strdel(&output);
        index++;
        if (args[index])
            printf(" ");
    }
    print_nl(is_nl);
    return 0;
}

static void print_nl(bool is_nl) {
    if (is_nl)
        printf("\n");
    else
        printf("\x1b[0;47;30m%%\x1b[0m\n");
}

static char *replace_escape(char *arg) {
    char *replace = mx_replace_substr(arg, "\x0a", "\\n");
    char *result = mx_strnew(ARG_MAX);

    copy(result, replace);
    replace = mx_replace_substr(result, "\x09", "\\t");
    copy(result, replace);
    replace = mx_replace_substr(result, "\x0b", "\\v");
    copy(result, replace);
    replace = mx_replace_substr(result, "\x07", "\\a");
    copy(result, replace);
    replace = mx_replace_substr(result, "\x09", "\\t");
    copy(result, replace);
    return result;
}

static void copy(char *result, char *replace) {
    strcpy(result, replace);
    mx_strdel(&replace);
}

static unsigned int set_flags(bool *is_nl, bool *is_e, char **argv) {
    unsigned int index = 0;

    while (argv[index]) {
        if (mx_match(argv[index], "^-[nEe]+$")) {
            for (unsigned int i = 0; i < strlen(argv[index]); i++) {
                if (argv[index][i] == 'E')
                    *is_e = true;
                if (argv[index][i] == 'e')
                    *is_e = false;
                if (argv[index][i] == 'n')
                    *is_nl = false;
            }
        }
        else {
            break;
        }
        index++;
    }
    return index;
}
