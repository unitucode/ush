#include "ush.h"

void mx_del_process(t_process **process) {
    free((*process)->attrs);
    free((*process)->actions);
    free(*process);
    process = NULL;
}
