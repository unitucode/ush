#include "ush.h"

static pid_t get_process_pid(char *input) {
    int id;

    if (input[0] == '%') {
        id = atoi(input + 1);
        return mx_get_process_pid_by_id(id);
    }
    return atoi(input);
}


int mx_fg(char **args) {
    pid_t pid = get_process_pid(args[0]);
    printf("\nPROCESS PID IN FUNCT = %d\n", pid);

    if (kill(pid, SIGCONT) < 0) {
        fprintf(stderr, "fg %d: job not found\n", pid);
        return -1;
    }
    tcsetpgrp(0, pid);
    return 0;
}
