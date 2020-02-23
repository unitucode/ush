#include "ush.h"

char *mx_str_prompt() {
    char *prompt = getenv("MX_PROMPT");

    mx_print_color(-1);
    return prompt;
}
