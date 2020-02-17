#include "ush.h"

static int exec_our(char *command, char **argv, int fd) {
    if (strcmp(command, "export") == 0)
        return mx_export(&argv[1], fd);
    if (strcmp(command, "unset") == 0)
        return mx_unset(&argv[1]);
    if (strcmp(command, "pwd") == 0)
        return mx_pwd(&argv[1], fd);
    if (strcmp(command, "cd") == 0)
        return mx_cd(&argv[1], fd);
    if (strcmp(command, "which") == 0)
        return mx_which(&argv[1], fd);
    if (strcmp(command, "echo") == 0)
        return mx_cd(&argv[1], fd);
    if (strcmp(command, "env") == 0)
        return mx_env(&argv[1], fd);
    if (strcmp(command, "fg") == 0)
        return mx_fg(&argv[1], fd);
    return -1337;
}

void mx_exec_command(char **argv, int fd) {
    char *filename = NULL;

    if (mx_is_our_command(argv[0]))
        exec_our(argv[0], argv, fd);
    else if (mx_find_command(getenv("PATH"), argv[0], &filename)) {
        t_process *process = mx_create_process(fd);
        extern char **environ;

        mx_exec(process, filename, argv, environ);
        mx_strdel(&filename);
        mx_del_process(&process);
    }
    else
        fprintf(stderr, "%s: command not found: %s\n",
                MX_SHELL_NAME, argv[0]);
}
