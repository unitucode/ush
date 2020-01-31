#include "ush.h"

bool mx_check_quotes(char *command) {
    bool s_quotes = false;
    bool grave_accent = false;
    
    for (unsigned int i = 0; i < strlen(command); i++) {
        if (command[i] == MX_S_QUOTE) {
            if (i > 1 && command[i - 1] == '\\'
                && command[i - 2] != '\\') {
                continue;
            }
            if (i == 1 && command[i - 1] == '\\')
                continue;
            s_quotes = !s_quotes;
        }
        if (command[i] == MX_GRAVE_ACCENT && !s_quotes) {
            grave_accent = !grave_accent;
        }
    }
    return !s_quotes && !grave_accent;
}
