#include "ush.h"

static void insert_char(t_prompt *prompt);
static void delete_char(t_prompt *prompt);

void mx_handle_print_char(t_prompt *prompt) {
    prompt->tmp_history = prompt->history_head;
    if (prompt->buff[0] == 0x15 && strlen(prompt->buff) == 1) {
        memset(prompt->command, '\0', sizeof(prompt->command));
        prompt->index = 0;
        return;
    }
    if (prompt->buff[0] == 0x7f && strlen(prompt->buff) == 1) {
        delete_char(prompt);
        return;
    }
    if (!isprint(prompt->buff[0]) || strlen(prompt->buff) != 1)
        return;
    insert_char(prompt);
}

static void delete_char(t_prompt *prompt) {
    unsigned int i_d = prompt->cursor_index - 1;

    if (!prompt->cursor_index || !prompt->index)
        return;
    memmove(prompt->command + i_d, prompt->command + i_d + 1,
    strlen(prompt->command) - i_d);
    prompt->index--;
    prompt->cursor_index--;
}

static void insert_char(t_prompt *prompt) {
    unsigned int c_i = prompt->cursor_index;

    memmove(prompt->command + c_i + 1, prompt->command + c_i,
    strlen(prompt->command + c_i));
    prompt->command[prompt->cursor_index] = prompt->buff[0];
    prompt->index++;
    prompt->cursor_index++;
}
