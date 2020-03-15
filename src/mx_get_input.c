#include "ush.h"

static void clear_prompt(t_prompt *prompt) {
    memset(prompt->command, '\0', sizeof(prompt->command));
    memset(prompt->tmp_command, '\0', sizeof(prompt->tmp_command));
    prompt->index = 0;
    prompt->cursor_index = 0;
    prompt->end = false;
}

static void set_code(t_prompt *prompt, int *code) {
    if (prompt->buff[0] == '\x03' && strlen(prompt->buff) == 1) {
        clear_prompt(prompt);
        *code = 130;
    }
    if (prompt->buff[0] == '\x04'
        && !prompt->index && strlen(prompt->buff) == 1) {
        *code = -1;
    }
}

static void clear_view(t_prompt *prompt, int fd) {
    mx_backspace(prompt->index + strlen(mx_str_prompt()), fd);
    dprintf(fd, "%s%s", mx_str_prompt(), prompt->command);
    mx_backspace(prompt->index + strlen(mx_str_prompt()), fd);
}

static bool handle_key(t_prompt *prompt, int fd, int *code) {
    set_code(prompt, code);
    if (mx_match(prompt->buff, MX_NEW_LINE_CHARS))
        return false;
    if (prompt->buff[0] == '\x04' && !prompt->index)
        return false;
    clear_view(prompt, fd);
    if (!mx_handle_history(prompt)) {
        mx_handle_print_char(prompt);
        strcpy(prompt->tmp_command, prompt->command);
    }
    return true;
}

void mx_get_input(t_prompt *prompt, int fd, int *code) {
    clear_prompt(prompt);
    dprintf(fd, "%s%s", mx_str_prompt(), prompt->command);
    while (read(STDIN_FILENO, prompt->buff, 4)
           && prompt->index < ARG_MAX
           && handle_key(prompt, fd, code)) {
        dprintf(fd, "%s%s", mx_str_prompt(), prompt->command);
        mx_handle_cursor(prompt);
        memset(prompt->buff, '\0', sizeof(prompt->buff));
    }
    mx_update_history(prompt);
}
