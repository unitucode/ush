#include "ush.h"

// static void check_parameter_sub(char *command, size_t len, bool *d_sub);

bool mx_check_substitutions(char *command) {
    bool g_quotes = false;
    // bool d_sub = false;
    size_t len = strlen(command);
    
    for (unsigned int i = 0; i < len; i++) {
        mx_skip_quotes(command, &i, '\'');
        mx_skip_expansion(command, &i);
        if (command[i] == MX_GRAVE_ACCENT && !mx_isescape_char(command, i)) {
            g_quotes = !g_quotes;
        }
    }
    // check_parameter_sub(command, len, &d_sub);
    return !g_quotes;
}

// static void check_parameter_sub(char *command, size_t len, bool *d_sub) {
//     for (unsigned int i = 0; i < len; i++) {
//         mx_skip_quotes(command, &i, '\'');
//         mx_skip_quotes(command, &i, '`');
//         if (command[i] == '$' && command[i + 1] == '('
//             && !mx_isescape_char(command, i)) {
//             *d_sub = true;
//         }
//         if (command[i] == ')' && !mx_isescape_char(command, i)) {
//             *d_sub = false;
//         }
//     }
// }
