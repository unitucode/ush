#include "ush.h"

int mx_preinterpretate(char *command) {
    if (!mx_check_quotes(command)) {
        fprintf(stderr, "%s: syntax error: missing terminating character\n", 
        MX_SHELL_NAME);
        return 1;
    }
    if (!mx_check_escape(command)) {
        fprintf(stderr, "%s: syntax error: illegal escape character\n",
        MX_SHELL_NAME);
        return 1;
    }
    return 0;
}
