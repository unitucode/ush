#include "ush.h"

void mx_skip_expansion(char *command, unsigned int *i) {
    int br = 0;

    if (command[*i] == '$' && !mx_isescape_char(command, *i)) {
        if (command[*i + 1] == '(' && !mx_isescape_char(command, *i)) {
            *i += 2;
            br++;
            while (command[*i]) {
                if (command[*i] == '(' && !mx_isescape_char(command, *i)) {
                    br++;
                }
                if (command[*i] == ')' && !mx_isescape_char(command, *i)) {
                    br--;
                }
                if (!br)
                    break;
                (*i)++;
            }
        }
    }
}
