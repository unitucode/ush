#include "ush.h"

bool mx_check_chars(char *command) {
    for (unsigned int i = 0; i < strlen(command); i++) {
        mx_skip_quotes(command, &i, MX_D_QUOTES);
        mx_skip_quotes(command, &i, MX_S_QUOTES);
        for (unsigned int j = 0; j < strlen(MX_FORBIDDEN_CHARS); j++) {
            if (command[i] == MX_FORBIDDEN_CHARS[j]
                && !mx_isescape_char(command, i)) {
                return false;
            }
        }
    }
    return true;
}
