#include "ush.h"

static char *get_var_name(char *str);
static void get_value(char **value, char *str, int space_index);

void mx_export(char *str) {
    char **strs = mx_strsplit(str, ' '); 
    bool flag = 0;

    for (int i = 0; strs[i]; i++) {
        char *value = mx_strdup("");
        int space_index = mx_get_char_index(strs[i], '=');
        char *env_var_name = get_var_name(strs[i]);

        if (strs[i][0] == '=' && !flag) {
            fprintf(stderr, "ush: bad assignment");
            flag = 1;
        }
        if (space_index != -1 && !flag)
            get_value(&value, strs[i], space_index);
        setenv(env_var_name, value, 1);
        mx_strdel(&env_var_name);
        mx_strdel(&value);
    }
    mx_del_strarr(&strs);
}

static void get_value(char **value, char *str, int space_index) {
    mx_strdel(value);
    *value = mx_strdup(str += space_index + 1);
}

static char *get_var_name(char *str) {
    char *name = mx_strndup(str, mx_get_char_index(str, '='));

    return name;
}
