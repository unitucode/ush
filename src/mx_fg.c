#include "ush.h"

static int get_pgid_by_job_id(int id)

int mx_fg(char *name) {
    int index = mx_get_char_index(name, ' ');
    char *pid = mx_strndup(name, index);
    int job_id = mx_atoi(pid);


    mx_strdel(&pid);
}

static int get_pgid_by_job_id(int id) {
    struct job *job = get_job_by_id(id);
}
