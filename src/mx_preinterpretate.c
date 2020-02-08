#include "ush.h"

int mx_preinterpretate(char *command) {
    if (!mx_check_quotes(command)) {
        fprintf(stderr, "%s: syntax error: missing terminating character\n", 
        MX_SHELL_NAME);
        return 1;
    }
    // if (!mx_check_brackets(command)) {
    //     fprintf(stderr, "%s: syntax error: missing brace character\n", 
    //     MX_SHELL_NAME);
    //     return 1;
    // }
    if (!mx_check_substitutions(command)) {
        fprintf(stderr, "%s: syntax error: missing subsitution character\n", 
        MX_SHELL_NAME);
        return 1;
    }
    return 0;
}
