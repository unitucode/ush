#include "ush.h"

t_process *mx_create_process(int fd) {
    t_process *process = malloc(sizeof(t_process));

    process->cmd = NULL;
    process->pos = 0;
    sigemptyset(&process->signals);
    sigaddset(&process->signals, SIGINT);
    if (fd == 1)
        sigaddset(&process->signals, SIGTSTP);
    posix_spawnattr_init(&process->attrs);
    posix_spawnattr_setsigdefault(&process->attrs, &process->signals);
    posix_spawnattr_setflags(&process->attrs,
                             POSIX_SPAWN_SETSIGDEF | POSIX_SPAWN_SETSIGMASK);
    posix_spawn_file_actions_init(&process->actions);
    posix_spawn_file_actions_adddup2(&process->actions, fd, 1);
    return process;
}
