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
    if (!prompt->index)
        return;
    prompt->command[--prompt->index] = '\0';
}

static void insert_char(t_prompt *prompt) {
    prompt->command[prompt->index++] = prompt->buff[0];
}
