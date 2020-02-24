#include "ush.h"

char *mx_str_prompt() {
    char *prompt = mx_get_var_val(SHELL, "MX_PROMPT");

    mx_print_color(-1);
    if (!prompt) {
        return MX_SHELL_PROMPT;
    }
    return prompt;
}
