#include "ush.h"

bool mx_isescape_char(char *command, int i) {
    if (i > 0 && command[i - 1] == '\\'
        && !mx_isescape_char(command, i - 1)) {
        return true;
    }
    if (i == 1 && command[i - 1] == '\\')
        return true;
    return false;
}
