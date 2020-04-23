#include "ush.h"

static void skip_single_quotes(char *command, unsigned int *i) {
    if (command[*i] == MX_S_QUOTES && !mx_isescape_char(command, *i)) {
        (*i)++;
        while (command[*i]) {
            if (command[*i] == MX_S_QUOTES) {
                break;
            }
            (*i)++;
        }
    }
}

void mx_skip_quotes(char *command, unsigned int *i, char c) {
    if (c == MX_S_QUOTES) {
        skip_single_quotes(command, i);
        return;
    }
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
