#include "ush.h"

static pid_t get_process_pid(char *input) {
    int id;

    if (input[0] == '%') {
        id = atoi(input + 1);
        return mx_get_process_pid_by_id(id);
    }
    return atoi(input);
}


int mx_fg(char **args, int fd) {
    pid_t pid = get_process_pid(args[0]);
    fd++;
    if (pid == -1) {
        fprintf(stderr, "fg: %s: no such job\n", args[0]);
        return -1;
    }
    if (kill(pid, SIGCONT) < 0) {
        fprintf(stderr, "fg: %d: job not found\n", pid);
        return -1;
    }
    tcsetpgrp(0, pid);
    return 0;
}
