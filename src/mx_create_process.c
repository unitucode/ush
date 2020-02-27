#include "ush.h"

static void set_signals(sigset_t *signals, int fd) {
    sigfillset(signals);
    sigdelset(signals, SIGINT);
    sigdelset(signals, SIGQUIT);
    sigdelset(signals, SIGCONT);
    sigdelset(signals, SIGCHLD);
    if (fd == 1)
        sigdelset(signals, SIGTSTP);
}

t_list *mx_get_last_process(t_list *processes) {
    for (t_list *cur = processes; cur; cur = cur->next) {
        if (!cur->next) {
            return cur;
        }
    }
    return NULL;
}

t_process *mx_create_process(int fd) {
    t_process *process = malloc(sizeof(t_process));

    process->cmd = NULL;
    process->pos = 0;
    process->fd = fd;
    process->gpid = 0;
    set_signals(&process->signals, fd);
    posix_spawnattr_init(&process->attrs);
    posix_spawnattr_setpgroup(&process->attrs, process->gpid);
    posix_spawnattr_setsigmask(&process->attrs, &process->signals);
    posix_spawnattr_setflags(&process->attrs, POSIX_SPAWN_SETSIGMASK
                             | POSIX_SPAWN_SETPGROUP);
    posix_spawn_file_actions_init(&process->actions);
    posix_spawn_file_actions_adddup2(&process->actions, fd, 1);
    return process;
}

