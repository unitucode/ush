#include "ush.h"

void mx_putenv(char *var) {
    static char name[1024];
    static char val[1024];
    char *received_name = mx_get_var_info(var, 0);
    char *received_val = mx_get_var_info(var, 1);

    sprintf(name, "%s", received_name);
    sprintf(val, "%s", received_val);
    setenv(name, val, 1);
    mx_strdel(&received_name);
    mx_strdel(&received_val);
}
