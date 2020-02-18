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
    int id = mx_get_process_id_by_pid(pid);
    int status;
    // t_process *process = mx_get_process_by_id(id);

    if (pid == -1) {
        fprintf(stderr, "fg: %s: no such job\n", args[0]);
        return -1;
    }
    if (kill(pid, SIGCONT) < 0) {
        fprintf(stderr, "fg: %d: job not found\n", pid);
        return -1;
    }
    tcsetpgrp(0, pid);
    dprintf(fd, "[%d] + %d continued %s\n", id, pid, "test");
    pid = waitpid(WAIT_ANY, &status, WUNTRACED);
    return 0;
}

// void wait_for_job (job *j)
// {
//   int status;
//   pid_t pid;

//   do
//     pid = waitpid (WAIT_ANY, &status, WUNTRACED);
//   while (!mark_process_status (pid, status)
//          && !job_is_stopped (j)
//          && !job_is_completed (j));
// }
