#include "ush.h"

void mx_del_process(t_process **process) {
    if (!MX_WIFSTOPPED((*process)->status)) {
        printf("deleted %d\n", (*process)->pid);
        free((*process)->attrs);
        free((*process)->actions);
        mx_del_strarr(&(*process)->cmd);
        free(*process);
        process = NULL;
    }
}
