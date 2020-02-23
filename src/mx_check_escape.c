#include "ush.h"

bool mx_check_escape(char *command) {
    for (unsigned int i = 0; command[i]; i++) {
        bool c = false;

        if (command[i] == '\\') {
            if (mx_isescape_char(command, i))
                continue;
            for (unsigned int j = 0; MX_ESCAPE_CHARS[j]; j++) {
                if (command[i + 1] == MX_ESCAPE_CHARS[j]) {
                    c = true;
                    break;
                }
            }
            if (!c)
                return c;
        }
    }
    return true;
}
