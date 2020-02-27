#include "ush.h"

static char *get_env(char *var, unsigned int *len, int add, char *arg) {
    char *result = mx_get_var_val(SHELL, var);

    if (result) {
        *len += add;
        return strdup(result);
    }
    return strndup(arg, 1);
}

static char *get_dir(char *arg, unsigned int *len,
                     unsigned int index, unsigned int save) {
    char *dir_name = NULL;
    char *tmp_name = NULL;
    char *user_in_file = NULL;

    tmp_name = strndup(arg + save, index - save);
    dir_name = mx_strjoin("/Users/", tmp_name);
    user_in_file = mx_check_user_file(tmp_name);
    if ((!mx_check_user(tmp_name) && !user_in_file) || !strcmp(tmp_name, ".")
        || !strcmp(tmp_name, "..") || !strcmp(tmp_name, "Shared")) {
        mx_strdel(&tmp_name);
        mx_strdel(&dir_name);
        return strndup(arg + save - 1, 1);
    }
    *len += index - save;
    mx_strdel(&tmp_name);
    if (user_in_file) {
        mx_strdel(&dir_name);
        return user_in_file;
    }
    return dir_name;
}

static char *get_tilde_sub(char *arg, unsigned int index, unsigned int *len) {
    bool is_last = false;
    unsigned int save = index + 1;

    *len = 0;
    index++;
    is_last = isspace(arg[index + 1]) || !arg[index + 1];
    if (arg[index] == '/' || isspace(arg[index]) || !arg[index])
        return get_env("HOME", len, 0, arg);
    if (arg[index] == '-' && (arg[index + 1] == '/' || is_last))
        return get_env("OLDPWD", len, 1, arg);
    if (arg[index] == '+' && (arg[index + 1] == '/' || is_last))
        return get_env("PWD", len, 1, arg);
    else if (arg[index]) {
        while (!isspace(arg[index]) && arg[index] != '/' && arg[index]) {
            index++;
        }
        return get_dir(arg, len, index, save);
    }
    return strndup(arg, 1);
}

static void add_sub(char *result, char *arg, unsigned int *i_s) {
    char *sub = NULL;

    strncat(result, arg + i_s[1], i_s[0] - i_s[1]);
    sub = get_tilde_sub(arg, i_s[0], &i_s[2]);
    strcat(result, sub);
    i_s[0] += i_s[2];
    i_s[1] = i_s[0] + 1;
    mx_strdel(&sub);
}

char *mx_replace_tilde(char *arg) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int i_s[3] = {0, 0, 0};
    bool is_quotes = false;

    for (; mx_get_char_index(&arg[i_s[0]], '~') >= 0; i_s[0]++) {
        mx_skip_exps_quots(arg, &i_s[0], &is_quotes);
        if ((arg[i_s[0]] == '~' && !mx_isescape_char(arg, i_s[0]))
            && ((i_s[0] > 0 && isspace(arg[i_s[0] - 1])
            && !mx_isescape_char(arg, i_s[0] - 1)) || (i_s[0] == 0))) {
            add_sub(result, arg, i_s);
        }
    }
    strcat(result, arg + i_s[1]);
    mx_strdel(&arg);
    return result;
}
