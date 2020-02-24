#include "ush.h"

static void check_status(t_list **processes);

int mx_jobs(char **args, int fd) {
    t_list **processes = mx_get_list_procs();
    t_process *tmp = NULL;

    if (mx_arr_size(args) > 0) {
        fprintf(stderr, "jobs: too many arguments\n");
        return 1;
    }
    check_status(processes);
    for (t_list *cur = *processes; cur; cur = cur->next) {
        tmp = (t_process*)cur->data;
        dprintf(fd, "[%d]    ", tmp->pos);
        dprintf(fd, "suspended  ");
        dprintf(fd, "%s\n", tmp->cmd);
    }
    return 0;
}

static void check_status(t_list **processes) {
    pid_t ret_pid = 0;
    t_process *tmp = NULL;

    for (t_list *cur = *processes; cur; cur = cur->next) {
        tmp = (t_process*)cur->data;
        ret_pid = waitpid(tmp->pid, &tmp->status, WNOHANG | WUNTRACED);
        if (!MX_WIFSTOPPED(tmp->status) || ret_pid == -1) {
            mx_del_node_list(processes, &tmp);
        }
    }
}
