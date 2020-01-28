#include "ush.h"

void mx_handle_arrows(t_prompt *prompt) {
    if (!strcmp(prompt->buff, MX_RIGHT_ARROW)) {
        if (prompt->index >= prompt->cursor_index) {
            prompt->cursor_index++;
            // printf(MX_MOVE_CURSOR_RIGHT);
        }
    }
    if (!strcmp(prompt->buff, MX_LEFT_ARROW)) {
        if (prompt->cursor_index) {
            // prompt->cursor_index--;
            printf(MX_MOVE_CURSOR_LEFT);
        }
    }
}
