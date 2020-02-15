#include "ush.h"

static char *get_tilde_sub(char *arg, unsigned int index, unsigned int *len);

char *mx_replace_tilde(char *arg) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int index = 0;
    unsigned int save = 0;
    unsigned int len = 0;
    char *sub = NULL;

    for (; mx_get_char_index(&arg[index], '~') >= 0; index++) {
        mx_skip_quotes(arg, &index, MX_GRAVE_ACCENT);
        mx_skip_quotes(arg, &index, MX_S_QUOTES);
        mx_skip_expansion(arg, &index);
        if ((arg[index] == '~' && !mx_isescape_char(arg, index)) && ((index > 0 && isspace(arg[index - 1]) && !mx_isescape_char(arg, index - 1)) || (index == 0))) {
            strncat(result, arg + save, index - save);
            sub = get_tilde_sub(arg, index, &len);
            strcat(result, sub);
            index += len;
            save = index + 1;
            mx_strdel(&sub);
        }
    }
    strcat(result, arg + save);
    mx_strdel(&arg);
    return result;
}

static char *get_tilde_sub(char *arg, unsigned int index, unsigned int *len) {
    char *result = NULL;
    unsigned int save = index + 1;
    char *dir_name = NULL;
    char *tmp_name = NULL;
    DIR *dir = NULL;

    *len = 0;
    index++;
    if (arg[index] == '-' && (arg[index + 1] == '/' || (isspace(arg[index + 1]) || !arg[index + 1]))) {
        result = getenv("OLDPWD");
        if (result) {
            *len = 1;
            return strdup(result);
        }
        return strndup(arg, 1);
    }
    if (arg[index] == '+' && (arg[index + 1] == '/' || (isspace(arg[index + 1]) || !arg[index + 1]))) {
        result = getenv("PWD");
        if (result) {
            *len = 1;
            return strdup(result);
        }
        return strndup(arg, 1);
    }
    if (arg[index] == '/' || isspace(arg[index]) || !arg[index]) {
        result = getenv("HOME");
        if (result) {
            return strdup(result);
        }
        return strndup(arg, 1);
    }
    else if (arg[index]) {
        while (!isspace(arg[index]) && arg[index] != '/' && arg[index]) {
            index++;
        }
        tmp_name = strndup(arg + save, index - save);
        dir_name = mx_strjoin("/Users/", tmp_name);
        if (!(dir = opendir(dir_name)) || !strcmp(tmp_name, ".") || !strcmp(tmp_name, "..") || !strcmp(tmp_name, "Shared")) {
            mx_strdel(&tmp_name);
            mx_strdel(&dir_name);
            return strndup(arg, 1);
        }
        closedir(dir);
        *len += index - save;
        mx_strdel(&tmp_name); 
        return dir_name;
    }
    return strndup(arg, 1);
}
