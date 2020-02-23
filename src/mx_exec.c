#include "ush.h"

<<<<<<< HEAD
static char *argv_to_str(char **argv);

=======
>>>>>>> 06c6bfff59d3a80382b068b10f19fd94c34fe8fc
int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    t_list **list = mx_get_list_procs();
    t_list *tmp = *list;
    int retval = 0;

<<<<<<< HEAD
    process->cmd = argv_to_str(argv);
=======
    process->cmd = mx_exec_copy_argv(argv);
>>>>>>> 06c6bfff59d3a80382b068b10f19fd94c34fe8fc
    mx_disable_canon();
    process->status = posix_spawn(&process->pid, filename, &process->actions,
                                  &process->attrs, argv, env);
    process->gpid = getpgid(process->pid);
    if (process->status) {
        retval = 126;
        fprintf(stderr, "%s: %s: %s\n", filename, strerror(process->status),
                MX_SHELL_NAME);
    }
    tcsetpgrp(STDOUT_FILENO, process->gpid);
    if (waitpid(process->gpid, &process->status, WUNTRACED) != -1) {
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
            printf("[%d]    %d suspended  %s\n", process->pos, process->pid, process->cmd);
        }
    }
    tcsetpgrp(STDOUT_FILENO, getpgrp());
    mx_enable_canon();
    return retval;
}
<<<<<<< HEAD

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
=======
>>>>>>> 06c6bfff59d3a80382b068b10f19fd94c34fe8fc
