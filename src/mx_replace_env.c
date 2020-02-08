#include "ush.h"

static char *get_spec_sub(char *arg);
static unsigned int get_len_spec(char *spec);

char *mx_replace_env(char *arg) {
    char *result = mx_strnew(ARG_MAX);
    int index = 0;
    char *env = NULL;
    char *save = arg;

    while ((index = mx_get_char_index(arg, '$')) >= 0) {
        env = get_spec_sub(arg + index);
        if (!mx_isescape_char(arg, index)) {
            strncat(result, arg, index);
            strcat(result, env);
        }
        arg += (!get_len_spec(arg + index) ? 1 : get_len_spec(arg + index));
        arg += index;
        mx_strdel(&env);
    }
    strcat(result, arg);
    mx_strdel(&save);
    return result;
}

static char *get_spec_sub(char *arg) {
    unsigned int i = 1;
    char *env = NULL;
    char *res = NULL;

    if (isalpha(arg[i]) || arg[i] == '_') {
        i = get_len_spec(arg);
        env = mx_strnew(i);
        strncpy(env, arg + 1, i - 1);
        res = getenv(env);
        mx_strdel(&env);
        return res != NULL ? strdup(res) : strdup("");
    }
    else if (isnumber(arg[i])) {
        while (isnumber(arg[i]))
            i++;
        return strndup(arg, i - 1);
    }
    return strndup(arg, 1);
}

static unsigned int get_len_spec(char *spec) {
    unsigned int i = 0;

    if (isalpha(spec[i + 1]) || spec[i + 1] == '_') {
        i++;
        while (isnumber(spec[i]) || isalpha(spec[i]) || spec[i] == '_')
            i++;
    }
    else if (isnumber(spec[i + 1])) {
        i++;
        while (isnumber(spec[i]))
            i++;
    }
    return i;
}

// void mx_replace_env(char **arguments) {
//     unsigned int i = 0;

//     while (arguments[i]) {
//         replace_env(arguments[i]);
//         i++;
//     }
// }

// static void replace_env(char *argument) {
//     int index = 0;

//     while ((index = mx_get_char_index(argument, '$')) != -1) {
        
//     }
// }
