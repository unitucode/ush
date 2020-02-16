#include "ush.h"

static char *get_substitution(int *o_sub, int *c_sub, unsigned int *i, char *arg);
static void get_quoted_sub(int *o_sub, int *c_sub, unsigned int *i, char *arg);
static void get_parameter_sub(int *o_sub, int *c_sub, unsigned int *i, char *arg);

char *mx_replace_substitution(char *arg, int *code) {
    int open_sub = -1;
    int close_sub = -1;
    unsigned int save = 0;
    bool is_quotes = false;
    char *sub = NULL;
    char *result = mx_strnew(ARG_MAX);

    for (unsigned int i = 0; i < strlen(arg); i++) {
        mx_skip_quotes(arg, &i, MX_S_QUOTES);
        if (arg[i] == MX_D_QUOTES && !mx_isescape_char(arg, i))
            is_quotes = !is_quotes;
        sub = get_substitution(&open_sub, &close_sub, &i, arg);
        if (sub) {
            strncat(result, arg + save, open_sub - save);
            if (!mx_get_sub(result, sub, is_quotes, code)) {
                *code = 1;
                return NULL;
            }
            i = close_sub;
            save = i + 1;
        }
        else if (open_sub != -1 && close_sub == -1 && !sub) {
            break;
        }
        open_sub = -1;
        close_sub = -1;
    }
    strcat(result, arg + save);
    mx_strdel(&arg);
    return result;
}

static char *get_substitution(int *o_sub, int *c_sub, unsigned int *i, char *arg) {
    if (arg[*i] == MX_GRAVE_ACCENT && !mx_isescape_char(arg, *i)) {
        get_quoted_sub(o_sub, c_sub, i, arg);
    }
    else if (arg[*i] == '$' && !mx_isescape_char(arg, *i)) {
        get_parameter_sub(o_sub, c_sub, i, arg);
    }
    if (*o_sub != -1 && *c_sub != -1)
        return strndup(arg + *o_sub, *c_sub - *o_sub + 1);
    return NULL;
}

static void get_quoted_sub(int *o_sub, int *c_sub, unsigned int *i, char *arg) {
    while (arg[*i]) {
        mx_skip_quotes(arg, i, MX_S_QUOTES);
        if (arg[*i] == MX_GRAVE_ACCENT && !mx_isescape_char(arg, *i) && *o_sub == -1) {
            *o_sub = *i;
            *i += 1;
            continue;
        }
        if (arg[*i] == MX_GRAVE_ACCENT && !mx_isescape_char(arg, *i)) {
            *c_sub = *i;
            *i += 1;
            break;
        }
        *i += 1;
    }
}

static void get_parameter_sub(int *o_sub, int *c_sub, unsigned int *i, char *arg) {
    unsigned int brace = 0;

    while (arg[*i]) {
        mx_skip_quotes(arg, i, MX_S_QUOTES);
        if (arg[*i] == '$' && arg[*i + 1] == '(' && !mx_isescape_char(arg, *i) && *o_sub == -1) {
            brace++;
            *o_sub = *i;
            *i += 2;
            continue;
        }
        if (arg[*i] == '(' && !mx_isescape_char(arg, *i)) {
            brace++;
        }
        if (arg[*i] == ')' && !mx_isescape_char(arg, *i)) {
            brace--;
            if (!brace) {
                *c_sub = *i;
                *i += 1;
                break;
            }
        }

        *i += 1;
    }
}
