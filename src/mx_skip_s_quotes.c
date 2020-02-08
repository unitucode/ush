#include "ush.h"

void mx_skip_s_quotes(char *command, unsigned int *i) {
    if (command[*i] == MX_S_QUOTES && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == MX_S_QUOTES
                && !mx_isescape_char(command, *i)) {
                break;
            }
            (*i)++;
        }
    }
}
