#include "ush.h"

void mx_del_process(t_process **process) {
    if (!MX_WIFSTOPPED((*process)->status)) {
        free((*process)->attrs);
        free((*process)->actions);
        free(*process);
        process = NULL;
    }
}
