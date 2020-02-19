#include "ush.h"

int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();

    mx_disable_canon();
    process->command = mx_arr_to_str(argv);
    process->status = posix_spawn(&process->pid, filename,
                         &process->actions, &process->attrs, argv, env);
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1) {
        if (MX_WIFSTOPPED(process->status)) {
            mx_push_back(list, process);
        }
    }
    mx_enable_canon();
    return process->status;
}
