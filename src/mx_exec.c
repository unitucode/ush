#include "ush.h"

int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();
    t_list *tmp = *list;
    int retval = 0;

    process->cmd = mx_exec_copy_argv(argv);
    mx_disable_canon();
    process->status = posix_spawn(&process->pid, filename, &process->actions,
                                  &process->attrs, argv, env);
    if (process->status) {
        retval = 126;
        fprintf(stderr, "%s: %s: %s\n", filename, strerror(process->status),
                MX_SHELL_NAME);
    }
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1)
        if (MX_WIFSTOPPED(process->status)) {
            while (tmp) {
                if (!tmp->next) {
                    break;
                }
                tmp = tmp->next;
            }
            mx_push_back(list, process);
            if (tmp)
                process->pos = ((t_process *)tmp->data)->pos + 1;
            else
                process->pos = 1;
        }
    mx_enable_canon();
    return retval;
}
