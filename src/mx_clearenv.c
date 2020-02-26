#include "ush.h"

void mx_clearenv(void) {
    extern char **environ;
    char **vars_to_del = NULL;
    char *delname = NULL;

    if (environ[0] != NULL) {
        vars_to_del = mx_env_copy();
        for (int i = 0; vars_to_del[i]; i++) {
            mx_get_name(vars_to_del[i], &delname);
            unsetenv(delname);
        }
        if (vars_to_del[0])
            mx_del_strarr(&vars_to_del);
        if (delname != NULL)
            mx_strdel(&delname);
    }
}
