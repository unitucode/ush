#include "ush.h"

static int get_pgid_by_job_id(int id);
static int get_pid(char *input, int *job_id);
static void continue_job(int pid, int *job_id);

int mx_fg(char **argv) {
    int *job_id;
    pid_t pid = get_pid(argv[0], &job_id);
    
    if (kill(-pid, SIGCONT) < 0) {
        fprintf(stderr, "fg %d: job not found\n", pid);
        return -1;
    }
    tcsetpgrp(0, pid);
    continue_job(pid, &job_id);
}

static void continue_job(int pid, int *job_id) {
    if (job_id > 0) {
        
    }
}

static int get_pid(char *input, int *job_id) {
    pid_t pid;

    if (input[0] == '%') {
        job_id = atoi(input[1] + 1);
        pid = get_pgid_by_job_id(job_id);
        if (pid < 0) {
            fprintf(stderr, "fg %s: no such job\n", input);
            return -1;
        }
    }
    else
        pid = atoi(input);
    return pid;
}

static int get_pgid_by_job_id(int id) {
    struct job *job = get_job_by_id(id);
}
