#include "ush.h"

static void set_code(char *buff, int *code, int index);
static bool handle_key(t_prompt *prompt, int *code);
static void clear_prompt(t_prompt *prompt);

void mx_get_input(t_prompt *prompt, int *code) {
    clear_prompt(prompt);
    while (read(STDIN_FILENO, prompt->buff, 4)
           && prompt->index < ARG_MAX
           && handle_key(prompt, code)) {
        printf("%s", prompt->command);
    }
}

static void set_code(char *buff, int *code, int index) {
    if (buff[0] == '\x03')
        *code = 130;
    if (buff[0] == '\x04' && !index)
        *code = -1;
}

static bool handle_key(t_prompt *prompt, int *code) {
    if (mx_match(prompt->buff, MX_NEW_LINE_CHARS))
        return false;
    if (prompt->buff[0] == '\x04' && !prompt->index)
        return false;
    mx_backspace(prompt->index);
    if (!mx_handle_history(prompt)) {
        mx_handle_print_char(prompt);
        strcpy(prompt->tmp_command, prompt->command);
    }
    set_code(prompt->buff, code, prompt->index);
    memset(prompt->buff, '\0', sizeof(prompt->buff));
    return true;
}

static void clear_prompt(t_prompt *prompt) {
    memset(prompt->command, '\0', sizeof(prompt->command));
    memset(prompt->tmp_command, '\0', sizeof(prompt->tmp_command));
    prompt->index = 0;
    prompt->ishistory = false;
}
