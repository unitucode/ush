#include "ush.h"

void mx_put_pwd(char *pwd, char *oldpwd) {
    char *new_pwd = mx_strjoin("PWD=", pwd);
    char *new_oldpwd = mx_strjoin("OLDPWD=", oldpwd);

    mx_var_list_insert(SHELL, new_pwd);
    mx_var_list_insert(EXP, new_pwd);
    mx_putenv(new_pwd);
    mx_var_list_insert(SHELL, new_oldpwd);
    mx_var_list_insert(EXP, new_oldpwd);
    mx_putenv(new_oldpwd);
    mx_strdel(&new_pwd);
    new_pwd = NULL;
    mx_strdel(&new_oldpwd);
    new_oldpwd = NULL;
}
