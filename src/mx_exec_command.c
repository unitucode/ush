#include "ush.h"

static int exec_builtin2(char *command, char **argv, int fd) {
    if (!strcmp(command, "pwd"))
        return mx_pwd(&argv[1], fd);
    if (!strcmp(command, "cd"))
        return mx_cd(&argv[1], fd);
    if (!strcmp(command, "echo"))
        return mx_echo(&argv[1], fd);
    if (!strcmp(command, "env"))
        return mx_env(&argv[1], fd);
    if (!strcmp(command, "fg"))
        return mx_fg(&argv[1], fd);
    if (!strcmp(command, "jobs"))
        return mx_jobs(&argv[1], fd);
    if (!strcmp(command, "set"))
        return mx_set(&argv[1], fd);
    if (!strcmp(command, "chdir"))
        return mx_chdir(&argv[1], fd);
    return 1;
}

static int exec_builtin1(char *command, char **argv, int fd) {
    if (!strcmp(command, "export"))
        return mx_export(&argv[1], fd);
    if (!strcmp(command, "which"))
        return mx_which(&argv[1], fd);
    if (!strcmp(command, "unset"))
        return mx_unset(&argv[1]);
    if (!strcmp(command, "color"))
        return mx_color(&argv[1]);
    if (!strcmp(command, "false"))
        return mx_false();
    if (!strcmp(command, "true"))
        return mx_true();
    if (!strcmp(command, "exit"))
        return mx_exit(&argv[1]);
    return exec_builtin2(command, argv, fd);
}

static int print_exec_error(char *error_name) {
    if (mx_match(error_name, "/"))
        fprintf(stderr, "%s: %s: No such file or directory\n",
                MX_SHELL_NAME, error_name);
    else
        fprintf(stderr, "%s: %s: Command not found\n",
                MX_SHELL_NAME, error_name);
    return 127;
}

int mx_exec_command(char **argv, int fd) {
    char *filename = NULL;
    int retval = 0;

    if (mx_is_builtin(argv[0])) {
        return exec_builtin1(argv[0], argv, fd);
    }
    else if (mx_find_command(mx_get_var_val(SHELL, "PATH"),
                             argv[0], &filename)) {
        extern char **environ;
        t_process *process = mx_create_process(fd);

        retval = mx_exec(process, filename, argv, environ);
        mx_del_process(&process);
        mx_strdel(&filename);
    }
    else
        retval = print_exec_error(argv[0]);
    return retval;
}
