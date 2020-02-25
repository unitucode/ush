#include "ush.h"

char *mx_str_prompt(void) {
    char *prompt = mx_get_var_val(SHELL, "MX_PROMPT");

    mx_print_color(-1);
    if (!isatty(2))
        return "";
    if (!prompt) {
        return MX_SHELL_PROMPT;
    }
    return prompt;
}
