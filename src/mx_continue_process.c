#include "ush.h"

void mx_continue_process(t_process *process, t_list **all_processes, int fd) {
    if (kill(-process->gpid, SIGCONT)) {
        fprintf(stderr, "fg: %s\n", strerror(errno));
    }
    dprintf(fd, "[%d]    %d continued  %s\n", process->pos, process->pid,
            process->cmd);
    if (waitpid(-process->gpid, &process->status, WUNTRACED) != -1) {
        if (!MX_WIFSTOPPED(process->status)) {
            mx_del_node_list(all_processes, &process);
        }
        else if (MX_WIFSTOPPED(process->status)) {
            printf("[%d]    %d suspended  %s\n", process->pos, process->pid,
                   process->cmd);
        }
    }
}
