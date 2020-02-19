#include "ush.h"

int mx_env_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();
    int retval = 0;

    mx_disable_canon();
    process->status = posix_spawn(&process->pid, filename,
                                  &process->actions, &process->attrs,
                                  argv, env);
    if (process->status) {
        retval = 126;
        fprintf(stderr, "env: %s: %s\n", filename, strerror(process->status));
    }
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1)
        if (WIFSTOPPED(process->status))
            mx_push_back(list, process);
    if (retval != 126)
        retval = MX_WEXITSTATUS(process->status);
    mx_enable_canon();
    return retval;
}
