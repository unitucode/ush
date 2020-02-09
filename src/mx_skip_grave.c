#include "ush.h"

void mx_skip_grave(char *command, unsigned int *i) {
    if (command[*i] == MX_GRAVE_ACCENT && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == MX_GRAVE_ACCENT
                && !mx_isescape_char(command, *i)) {
                break;
            }
            (*i)++;
        }
    }
}
