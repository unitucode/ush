#include "ush.h"

t_process *mx_create_process(int fd) {
    t_process *process = malloc(sizeof(t_process));

    process->cmd = NULL;
    process->pos = 0;
    process->fd = fd;
    process->gpid = 0;
    sigfillset(&process->signals);
    sigdelset(&process->signals, SIGINT);
    sigdelset(&process->signals, SIGQUIT);
    sigdelset(&process->signals, SIGCONT);
    sigdelset(&process->signals, SIGCHLD);
    if (fd == 1)
        sigdelset(&process->signals, SIGTSTP);
    posix_spawnattr_init(&process->attrs);
    posix_spawnattr_setpgroup(&process->attrs, process->gpid);
    posix_spawnattr_setsigmask(&process->attrs, &process->signals);
    posix_spawnattr_setflags(&process->attrs, POSIX_SPAWN_SETSIGMASK | POSIX_SPAWN_SETPGROUP);
    posix_spawn_file_actions_init(&process->actions);
    posix_spawn_file_actions_adddup2(&process->actions, fd, 1);
    return process;
}
