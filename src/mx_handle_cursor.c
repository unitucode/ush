#include "ush.h"

static void set_cursor(t_prompt *prompt);

void mx_handle_cursor(t_prompt *prompt) {
    if (!strcmp(prompt->buff, MX_RIGHT_ARROW)) {
        if (prompt->cursor_index < prompt->index)
            prompt->cursor_index++;
    }
    if (!strcmp(prompt->buff, MX_LEFT_ARROW)) {
        if (prompt->cursor_index)
            prompt->cursor_index--;
    }
    set_cursor(prompt);
}

static void set_cursor(t_prompt *prompt) {
    unsigned int move_left = prompt->index - prompt->cursor_index;

    for (unsigned int i = 0; i < move_left; i++) {
        printf("\b");
    }
}
