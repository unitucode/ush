#include "ush.h"

void mx_skip_exps_quots(char *arg, unsigned int *index, bool *is_quotes) {
    if (arg[*index] == MX_D_QUOTES && !mx_isescape_char(arg, *index))
            *is_quotes = !*is_quotes;
    if (!*is_quotes)
        mx_skip_quotes(arg, index, MX_S_QUOTES);
    mx_skip_quotes(arg, index, MX_GRAVE_ACCENT);
    mx_skip_expansion(arg, index);
}

bool mx_replace_env_var(char *result, char *env, unsigned int *index,
                        unsigned int len) {
    if (!env) {
        return false;
    }
    strcat(result, env);
    index[0] += len;
    index[1] = index[0] + 1;
    mx_strdel(&env);
    return true;
}

void mx_inc_val_var(unsigned int *len, unsigned int add, char *var) {
    *len += add;
    mx_strdel(&var);
}

void mx_skip_quotes_if(bool *is_quotes, char *arg, unsigned int *i) {
    if (arg[*i] == MX_D_QUOTES && !mx_isescape_char(arg, *i))
            *is_quotes = !*is_quotes;
    if (!*is_quotes)
        mx_skip_quotes(arg, i, MX_S_QUOTES);
}
