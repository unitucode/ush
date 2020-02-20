#include "ush.h"

static char *get_flag_arg(char **args, int *flag_idx, int *retval, int *idx) {
    if (args[0][(*flag_idx) + 1] == '\0')
        if (args[1] == NULL)
            *retval = mx_print_env_error(args[0][*flag_idx], NULL, 1);
        else {
            *flag_idx = -1;
            (*idx)++;
            return strdup(args[1]);
        }
    else {
        int shift = (*flag_idx) + 1;

        *flag_idx = -1;
        return strdup(args[0] + shift);
    }
    return NULL;
}

static void delete_var(char **delname) {
    unsetenv(*delname);
    if (delname != NULL)
        mx_strdel(delname);
}

static void env_check_delname(char *delname, int *retval) {
    if (!(*retval)) {
        *retval = mx_match(delname, "=");
        if (*retval)
            mx_print_env_error(0, delname, 2);
    }
}

int parse_flag(char **args, char **path, int *idx) {
    int retval = 0;

    for (int i = 1; args[0][i] != '\0'; i++) {
        if (args[0][i] == 'P') {
            if (*path != NULL)
                mx_strdel(path);
            *path = get_flag_arg(args, &i, &retval, idx);
        }
        else if (args[0][i] == 'u') {
            char *delname = get_flag_arg(args, &i, &retval, idx);

            env_check_delname(delname, &retval);
            delete_var(&delname);
        }
        else if (args[0][i] != 'i' && args[0][i] != '-')
            return mx_print_env_error(args[0][i], NULL, 0);
        if (retval || i == -1)
            break;
    }
    return retval;
}

int mx_env_parse_flags(char **argv, char **path, int *idx) {
    int retval = 0;
    bool flag_stop = 0;
    extern char **environ;

    for (*idx = 0; argv[*idx] && !flag_stop && !retval; ) {
        if (argv[*idx][0] == '-' && strcmp(argv[*idx], "--") != 0) {
            if (mx_match(argv[*idx], MX_ENV_FLAG_I))
                mx_clearenv();
            retval = parse_flag(&argv[*idx], path, idx);
        }
        else {
            if (strcmp(argv[*idx], "--") != 0)
                (*idx)--;
            flag_stop = 1;
        }
        (*idx)++;
    }
    return retval;
}
