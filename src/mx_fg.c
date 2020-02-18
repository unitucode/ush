#include "ush.h"

static pid_t get_process_pid(char *input) {
    int id;

    if (input[0] == '%') {
        id = atoi(input + 1);
        return mx_get_process_pid_by_id(id);
    }
    return atoi(input);
}

void outputList() {
    t_list **list = mx_get_list_procs();
    t_list *current = *list;
    mx_printstr("\n=================\nSTART\n=================\n");
    for (int i = 1; current != NULL; i++) {
        printf("#%d pid = %d\n", i, ((t_process *)current->data)->pid);
        current = current->next;
    }
    mx_printstr("==================\nEND\n==================\n");
}

int mx_fg(char **args, int fd) {
    pid_t pid = get_process_pid(args[0]);
    int id = mx_get_process_id_by_pid(pid);
    int status = 0;
    // t_process *process = mx_get_process_by_id(id);
    
    // outputList();
    if (pid == -1) {
        fprintf(stderr, "fg: %s: no such job\n", args[0]);
        return 0;
    }
    if (kill(pid, SIGCONT) < 0) {
        fprintf(stderr, "fg: %d: job not found\n", pid);
        return 0;
    }
    tcsetpgrp(0, pid);
    // dprintf(fd, "[%d] + %d continued %s\n", id, pid, "test");
    // pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    fd++;
    status++;
    id++;
    return 1;
}
