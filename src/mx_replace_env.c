#include "ush.h"

static char *get_spec_sub(char *arg, unsigned int index, unsigned int *len);
static bool is_spec(char c);

char *mx_replace_env(char *arg, int *code) {
    char *result = mx_strnew(ARG_MAX);
    unsigned int len = 0;
    char *env = NULL;
    unsigned int index = 0;
    unsigned int save = 0;

    for (; mx_get_char_index(&arg[index], '$') >= 0; index++) {
        mx_skip_quotes(arg, &index, MX_GRAVE_ACCENT);
        mx_skip_quotes(arg, &index, MX_S_QUOTES);
        mx_skip_expansion(arg, &index);
        if (arg[index] == '$' && !mx_isescape_char(arg, index)) {
            strncat(result, arg + save, index - save);
            env = get_spec_sub(arg, index, &len);
            if (!env) {
                *code = 1;
                return NULL;
            }
            strcat(result, env);
            index += len;
            save = index;
            mx_strdel(&env);
        }
    }
    strcat(result, arg + save);
    mx_strdel(&arg);
    return result;
}

static char *get_spec_sub(char *arg, unsigned int index, unsigned int *len) {
    char key[2] = "";
    t_map **map = mx_get_lenv();

    index++;
    if (arg[index] == '{') {
        *len = 2;
        index++;
    }
    if (is_spec(arg[index])) {
        key[0] = arg[index];
        *len += 2;
        return strdup(mx_get_map(map, key));
    }
    *len = 0;
    return strndup(arg, 0);
}

static bool is_spec(char c) {
    for (unsigned int i = 0; i < strlen(MX_SPEC_ENV); i++) {
        if (c == MX_SPEC_ENV[i]) {
            return true;
        }
    }
    return false;
}
