#include "ush.h"

void mx_del_process(t_process **process) {
    if (!MX_WIFSTOPPED((*process)->status)) {
        posix_spawnattr_destroy(&(*process)->attrs);
        posix_spawn_file_actions_destroy(&(*process)->actions);
        mx_strdel(&(*process)->cmd);
        free(*process);
        process = NULL;
    }
}

void mx_kill_process(void) {
    t_list **processes = mx_get_list_procs();
    t_process *tmp = NULL;

    for (t_list *cur = *processes; cur; cur = cur->next) {
        tmp = (t_process*)cur->data;
        kill(-tmp->gpid, SIGKILL);
        mx_del_node_list(processes, &tmp);
    }
}
