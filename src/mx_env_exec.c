#include "ush.h"

static char *argv_to_str(char **argv) {
    char str[ARG_MAX] = "";

    for (unsigned int i = 0; argv[i]; i++) {
        strcat(str, argv[i]);
        if (argv[i + 1]) {
            strcat(str, " ");
        }
    }
    return strdup(str);
}

static bool run_process(t_process *process,
                        char *filename, char **argv, char **env) {
    process->cmd = argv_to_str(argv);
    process->status = posix_spawn(&process->pid, filename, &process->actions,
                                  &process->attrs, argv, env);
    process->gpid = getpgid(process->pid);
    tcsetpgrp(STDOUT_FILENO, process->gpid);
    if (process->status) {
        return false;
    }
    return true;
}

static void add_process(t_process *process) {
    t_list **list = mx_get_list_procs();
    t_list *tmp = *list;

    while (tmp) {
        if (!tmp->next)
            break;
        tmp = tmp->next;
    }
    mx_push_back(list, process);
    if (tmp)
        process->pos = ((t_process*)tmp->data)->pos + 1;
    else
        process->pos = 1;
    printf("[%d]    %d suspended  %s\n", process->pos, process->pid,
           process->cmd);
}

int mx_env_exec(t_process *process, char *filename, char **argv, char **env) {
    int retval = 0;

    mx_disable_canon();
    if (!run_process(process, filename, argv, env)) {
        fprintf(stderr, "env: %s: %s\n", filename, strerror(process->status));
        retval = 126;
    }
    else if (waitpid(process->pid, &process->status, WUNTRACED) != -1)
        if (MX_WIFSTOPPED(process->status))
            add_process(process);
    tcsetpgrp(STDOUT_FILENO, getpgrp());
    mx_enable_canon();
    return retval != 126 ? MX_WEXITSTATUS(process->status) : retval;
}
