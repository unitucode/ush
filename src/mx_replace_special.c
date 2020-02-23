#include "ush.h"

static char *get_var(char *cmd, unsigned int *i);

char *mx_replace_special(char *command) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int r_i = 0;
    char *var = NULL;
    bool s_quotes = false;
    bool g_quotes = false;

    for (unsigned int i = 0; i < strlen(command); i++) {
        if (command[i] == MX_GRAVE_ACCENT && !mx_isescape_char(command, i) && !s_quotes) {
            g_quotes = !g_quotes;
        }
        if (command[i] == MX_S_QUOTES && !mx_isescape_char(command, i)) {
            s_quotes = !s_quotes;
        }
        if (!s_quotes && !g_quotes) {
            while (command[i] == '$' && !mx_isescape_char(command, i)) {
                i++;
                var = get_var(command, &i);
                if (var) {
                    strcat(result, var);
                    r_i += strlen(var);
                    mx_strdel(&var);
                }
                else {
                    break;
                }
            }
        }
        if (!(command[i] == MX_D_QUOTES && !mx_isescape_char(command, i)) &&
            !(command[i] == MX_S_QUOTES && !mx_isescape_char(command, i)))
            result[r_i++] = command[i]; 
    }
    mx_strdel(&command);
    return result;
}

static char *get_var(char *cmd, unsigned int *i) {
    char *result = NULL;
    unsigned int save = *i;
    char *env = NULL;

    if (isalpha(cmd[*i]) || cmd[*i] == '_') {
        *i += 1;
        while (isalpha(cmd[*i]) || isnumber(cmd[*i]) || cmd[*i] == '_') {
            *i += 1;
        }
    }
    else {
        *i -= 1;
        return NULL;
    }
    result = strndup(cmd + save, *i - save);
    if (mx_get_var_val(EXP, result))
        env = strdup(mx_get_var_val(EXP, result));
    mx_strdel(&result);
    return env;
}
