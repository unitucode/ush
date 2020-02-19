#include "ush.h"

void mx_del_process(t_process **process) {
    if (WIFSTOPPED((*process)->status)) {
        free((*process)->attrs);
        free((*process)->actions);
        free(*process);
        process = NULL;
    }
}
