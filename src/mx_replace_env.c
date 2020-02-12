#include "ush.h"

static char *get_brace_sub(char *arg, unsigned int index, unsigned int *len);
static char *get_spec_sub(char *arg, unsigned int index, unsigned int *len);
static unsigned int get_len_spec(char *spec);
static char *check_spec_char(char *arg, unsigned int *len, unsigned int var_len);

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
            save = index + 1;
            mx_strdel(&env);
        }
    }
    strcat(result, arg + index);
    mx_strdel(&arg);
    return result;
}

static char *check_spec_char(char *arg, unsigned int *len, unsigned int var_len) {
    t_map **map = mx_get_lenv();
    char key[2];
    unsigned int l_s = var_len ? var_len : get_len_spec(arg);

    if (l_s > 1)
        return NULL;
    for (unsigned int i = 0; i < strlen(MX_SPEC_ENV); i++) {
        if (*arg == MX_SPEC_ENV[i]) {
            strncpy(key, arg, 1);
            *len += 1;
            return strdup(mx_get_map(map, key));
        }
    }
    return NULL;
}

static char *get_brace_sub(char *arg, unsigned int index, unsigned int *len) {
    int close_index = mx_get_char_index(arg + index + 1, '}');
    char *var = strndup(arg + index + 1, close_index);
    char *env = NULL;

    if ((env = check_spec_char(arg + index + 1, len, strlen(var)))) {
        *len += 2;
        mx_strdel(&var);
        return env;
    }
    if (mx_match(var, "^[0-9]*$")) {
        *len = strlen(var) + 2;
        mx_strdel(&var);
        return strdup("");
    }
    else if (!mx_match(var, "^[A-Za-z_]+[A-Za-z0-9_]*$") && strlen(var)) {
        mx_strdel(&var);
        return NULL;
    }
    *len = strlen(var) + 2;
    env = getenv(var);
    mx_strdel(&var);
    return env ? strdup(env) : strdup("");
}

static char *get_spec_sub(char *arg, unsigned int index, unsigned int *len) {
    char *var = NULL;
    char *env = NULL;

    index++;
    *len = 0;
    if ((env = check_spec_char(arg + index, len, 0)))
        return env;
    if (arg[index] == '{')
        return get_brace_sub(arg, index, len);
    if (isalpha(arg[index]) || arg[index] == '_') {
        *len = get_len_spec(arg + index);
        var = strndup(arg + index, *len);
        env = getenv(var);
        *len = strlen(var);
        mx_strdel(&var);
        return env ? strdup(env) : strdup("");
    }
    else if (isnumber(arg[index])) {
        *len = 1;
        return strdup("");
    }
    return strndup(arg, 1);
}

static unsigned int get_len_spec(char *spec) {
    unsigned int i = 1;

    if (isalpha(spec[i]) || spec[i] == '_') {
        i++;
        while (isnumber(spec[i]) || isalpha(spec[i]) || spec[i] == '_')
            i++;
    }
    else if (isnumber(spec[i])) {
        i++;
        while (isnumber(spec[i]))
            i++;
    }
    return i;
}
