#include "ush.h"

static void copy_environ(char **copy, char **environ) {
    for (int i = 0; environ[i]; i++) {
        copy[i] = strdup(environ[i]);
        if (environ[i + 1] == NULL)
            copy[i + 1] = NULL;
    }
}

static char **get_sorted_environ(void) {
    char **sorted_environ = NULL;
    extern char **environ;
    int len = 0;

    if (*environ == NULL)
        mx_putenv("SHLVL=0");
    while (environ[len])
        len++;
    sorted_environ = malloc((len + 1) * sizeof(char*));
    copy_environ(sorted_environ, environ);
    mx_bubble_sort(sorted_environ, len);
    return sorted_environ;
}

void mx_init_var_lists(void) {
    t_list **shell_list = mx_get_var_list(SHELL);
    t_list **exp_list = mx_get_var_list(EXP);
    char **sorted_environ = get_sorted_environ();

    for (int i = 0; sorted_environ[i]; i++) {
        mx_push_back(shell_list, strdup(sorted_environ[i]));
        mx_push_back(exp_list, strdup(sorted_environ[i]));
    }
    mx_del_strarr(&sorted_environ);
}
