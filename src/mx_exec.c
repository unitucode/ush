#include "ush.h"

static char **copy_argv(char **argv);

int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();
    t_list *tmp = *list;
    int retval = 0;

    process->cmd = copy_argv(argv);
    mx_disable_canon();
    process->status = posix_spawn(&process->pid, filename,
                         &process->actions, &process->attrs, argv, env);
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1) {
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
    }
    mx_enable_canon();
    return retval;
}

static char **copy_argv(char **argv) {
    size_t size = mx_arr_size(argv);
    char **copy = malloc(sizeof(char *) * (size + 1));

    copy[size] = NULL;
    for (unsigned int i = 0; i < size; i++) {
        copy[i] = strdup(argv[i]);
    }
    return copy;
}
