#include "ush.h"

void mx_exec_fork(char **arguments, int fd) {
    pid_t child = fork();

    if (!child) {
        mx_exec_command(arguments, fd);
        exit(0);
    }
    waitpid(child, NULL, 0);
}
