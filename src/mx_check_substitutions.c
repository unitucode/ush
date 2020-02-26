#include "ush.h"

bool mx_check_substitutions(char *command) {
    bool g_quotes = false;
    size_t len = strlen(command);

    for (unsigned int i = 0; i < len; i++) {
        mx_skip_quotes(command, &i, MX_S_QUOTES);
        mx_skip_expansion(command, &i);
        if (command[i] == MX_GRAVE_ACCENT && !mx_isescape_char(command, i)) {
            g_quotes = !g_quotes;
        }
    }
    return !g_quotes;
}
