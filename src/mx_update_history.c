#include "ush.h"

void mx_update_history(t_prompt *prompt) {
    if (prompt->buff[0] == '\x03' && strlen(prompt->buff) == 1)
        return;
    if (!strlen(prompt->command))
        return;
    if (prompt->history_head &&
        !strcmp(prompt->command, prompt->history_head->data)) {
        return;
    }
    if (mx_d_list_size(prompt->history_head) == MX_HISTORY_SIZE)
        mx_d_pop_back(&prompt->history_head);
    mx_d_push_front(&prompt->history_head, strdup(prompt->command));
    prompt->tmp_history = prompt->history_head;
}
