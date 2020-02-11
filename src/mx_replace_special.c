#include "ush.h"

static char *get_var(char *cmd, unsigned int *i);
// static char *replace_all_escape(char *arg);
// static char *replace_arg_quotes(char *arg);

// char *mx_replace_special(char *argument) {
//     char *tmp_trim = mx_strtrim(argument);
//     char *arg = mx_strnew(ARG_MAX);

//     strcpy(arg, tmp_trim);
//     // arg = replace_arg_quotes(arg);
//     arg = replace_all_escape(arg);
//     mx_strdel(&tmp_trim);
//     mx_strdel(&argument);
//     return arg;
// }

// static char *replace_arg_quotes(char *arg) {
//     unsigned int len = strlen(arg);

//     if (arg[len - 1] == '\"' && !mx_isescape_char(arg, len - 1)) {
//         arg[len - 1] = '\0';
//     }
//     if (arg[0] == '\"' && !mx_isescape_char(arg, 0)) {
//         memmove(arg, arg + 1, len - 1);
//     }
//     return arg;
// }

// static char *replace_all_escape(char *arg) {
//     char *save = arg;
//     char *replace = mx_strnew(ARG_MAX);
//     unsigned int replace_index = 0;
//     bool g_a = false;
    
//     for (unsigned int i = 0; i < strlen(arg); i++) {
//         if (arg[i + 1] != '\\' && mx_isescape_char(arg, i + 1) && !g_a) {
//             i++;
//         }
//         replace[replace_index] = arg[i];
//         replace_index++;
//     }
//     mx_strdel(&save);
//     save = mx_replace_substr(replace, "\\\\", "\\");
//     strcpy(replace, save);
//     mx_strdel(&save);
//     return replace;
// }

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
