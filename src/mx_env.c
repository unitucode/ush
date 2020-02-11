#include "ush.h"

int mx_env() {
    t_process *process = mx_create_process(1);
    char *argv[20] = {"env", "ls", "-R", "/", NULL};
    extern char **environ;
    mx_exec(process, "/usr/bin/env", argv, environ);
    return 0;
}
