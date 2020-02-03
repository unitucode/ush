#include "ush.h"

bool mx_check_quotes(char *command) {
    bool s_quotes = false;
    bool grave_accent = false;
    
    for (unsigned int i = 0; i < strlen(command); i++) {
        if (command[i] == MX_D_QUOTES && !mx_isescape_char(command, i)) {
            s_quotes = !s_quotes;
        }
        if (command[i] == MX_GRAVE_ACCENT && !s_quotes
            && !mx_isescape_char(command, i)) {
            grave_accent = !grave_accent;
        }
    }
    return !s_quotes && !grave_accent;
}
