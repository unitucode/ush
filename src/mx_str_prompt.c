#include "ush.h"

char *mx_str_prompt() {
    char *prompt = getenv("MX_PROMPT");

    return prompt;
}
