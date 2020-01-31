#include "ush.h"

int mx_preinterpretate(char *command) {
    if (!mx_check_quotes(command)) {
        fprintf(stderr, "%s: error: missing terminating character\n", 
        MX_SHELL_NAME);
        return 1;
    }
    return 0;
}
