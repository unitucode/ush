#include "ush.h"

void mx_skip_quotes(char *command, unsigned int *i, char c) {
    if (command[*i] == c && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == c
                && !mx_isescape_char(command, *i)) {
                break;
            }
            (*i)++;
        }
    }
}
