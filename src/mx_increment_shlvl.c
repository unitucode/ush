#include "ush.h"

void mx_increment_shlvl(void) {
    int new_lvl = 1;
    char *curr_lvl = mx_get_var_val(SHELL, "SHLVL");
    char shlvl[NAME_MAX];
    char *arg[2] = {NULL, NULL};

    if (curr_lvl != NULL)
        new_lvl += atoi(curr_lvl);
    sprintf(shlvl, "SHLVL=%d", new_lvl);
    arg[0] = strdup(shlvl);
    mx_export(arg, 1);
    mx_strdel(&arg[0]);
}
