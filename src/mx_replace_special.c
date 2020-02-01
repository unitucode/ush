#include "ush.h"

static char *replace_all_escape(char *arg);
static char *replace_all_special(char *arg);

char *mx_replace_special(char *argument) {
    char *tmp_trim = mx_strtrim(argument);
    char *arg = mx_strnew(ARG_MAX);

    strcpy(arg, tmp_trim);
    arg = replace_all_escape(arg);
    printf("arg_replace = %s\n", arg);
    arg = replace_all_special(arg);
    printf("arg = %s\n", arg);
    mx_strdel(&tmp_trim);
    return arg;
}

static char *replace_all_special(char *arg) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int var_i = 0;
    char *var = NULL;
    char *env = NULL;

    for (unsigned int i = 0; i < strlen(arg); i++) {
        if (arg[i] == '$' && !mx_isescape_char(arg, i)) {
            if (isalpha(arg[i + 1]) || arg[i + 1] == '_') {
                var_i = i + 2;
                while (isalpha(arg[var_i]) || isnumber(arg[var_i]) || arg[var_i] == '_') {
                    var_i++;
                }
                var = mx_strnew(var_i - i);
                var = strncpy(var, arg + i + 1, var_i - i);
                env = getenv(var);
                printf("env = %s, var = %s, var_len = %d, arg = %s[%d]\n", env, var, var_i, arg + i, i);
                if (env)
                    strcat(result, env);
            }
        }
        result[i] = arg[i];
    }
    return result;
}

static char *replace_all_escape(char *arg) {
    arg = mx_replace_escape(arg, "\\n", '\x0a', true);
    arg = mx_replace_escape(arg, "\\t", '\x09', true);
    arg = mx_replace_escape(arg, "\\v", '\x0b', true);
    arg = mx_replace_escape(arg, "\\a", '\x07', true);
    arg = mx_replace_escape(arg, "\\\"", '\"', false);
    arg = mx_replace_escape(arg, "\\ ", ' ', false);
    return arg;
}
