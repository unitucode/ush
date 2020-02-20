#include "ush.h"

static int exec_builtin2(char *command, char **argv, int fd) {
    if (strcmp(command, "pwd") == 0)
        return mx_pwd(&argv[1], fd);
    if (strcmp(command, "cd") == 0)
        return mx_cd(&argv[1], fd);
    if (strcmp(command, "echo") == 0)
        return mx_echo(&argv[1], fd);
    if (strcmp(command, "env") == 0)
        return mx_env(&argv[1], fd);
    if (strcmp(command, "fg") == 0)
        return mx_fg(&argv[1], fd);
    return 1;
}

static int exec_builtin1(char *command, char **argv, int fd) {
    if (strcmp(command, "export") == 0)
        return mx_export(&argv[1], fd);
    if (strcmp(command, "which") == 0)
        return mx_which(&argv[1], fd);
    if (strcmp(command, "unset") == 0)
        return mx_unset(&argv[1]);
    if (strcmp(command, "color") == 0)
        return mx_color(&argv[1]);
    if (strcmp(command, "false") == 0)
        return mx_false();
    if (strcmp(command, "true") == 0)
        return mx_true();
    if (strcmp(command, "exit") == 0)
        mx_exit(&argv[1]);
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

    if (mx_is_builtin(argv[0]))
        return exec_builtin1(argv[0], argv, fd);
    else if (mx_find_command(getenv("PATH"), argv[0], &filename)) {
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
