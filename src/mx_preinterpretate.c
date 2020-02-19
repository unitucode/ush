#include "ush.h"

int mx_preinterpretate(char *command) {
    int result = 0;

    if (!(result = mx_check_quotes(command))) {
        fprintf(stderr, "%s: syntax error: missing terminating character\n", 
        MX_SHELL_NAME);
    }
    else if (!(result = mx_check_brackets(command))) {
        fprintf(stderr, "%s: syntax error: missing brace character\n", 
        MX_SHELL_NAME);
    }
    else if (!(result = mx_check_substitutions(command))) {
        fprintf(stderr, "%s: syntax error: missing subsitution character\n", 
        MX_SHELL_NAME);
    }
    else if (!(result = mx_check_chars(command))) {
        fprintf(stderr, "%s: command contain forbidden character\n",
        MX_SHELL_NAME);
    }
    return !result;
}
