#include "ush.h"

bool mx_check_quotes(char *command) {
    size_t len = strlen(command);
    bool s_quotes = false;
    bool d_quotes = false;

    for (unsigned int i = 0; i < len; i++) {
        if (!s_quotes) {
            mx_skip_quotes(command, &i, MX_GRAVE_ACCENT);
            mx_skip_expansion(command, &i);
        }
        if (command[i] == MX_D_QUOTES
            && !mx_isescape_char(command, i) && !s_quotes) {
            d_quotes = !d_quotes;
        }
        if (command[i] == MX_S_QUOTES && !d_quotes) {
            if (!s_quotes) {
                if (!mx_isescape_char(command, i)) {
                    s_quotes = !s_quotes;
                }
            }
            else if (s_quotes)
                s_quotes = !s_quotes;
        }
    }
    return !s_quotes && !d_quotes;
}
