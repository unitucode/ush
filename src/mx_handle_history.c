#include "ush.h"

static void get_down_history(t_prompt *prompt);
static void get_up_history(t_prompt *prompt);

bool mx_handle_history(t_prompt *prompt) {
    if (!strcmp(prompt->buff, MX_DOWN_ARROW)) {
        get_down_history(prompt);
        return true;
    }
    if (!strcmp(prompt->buff, MX_UP_ARROW)) {
        get_up_history(prompt);
        return true;
    }
    return false;
}

static void get_down_history(t_prompt *prompt) {
    t_d_list *tmp = prompt->tmp_history->prev;
    while (tmp) {
        prompt->tmp_history = prompt->tmp_history->prev;
        if (!mx_get_substr_index(prompt->tmp_history->data, prompt->tmp_command)) {
            strcpy(prompt->command, prompt->tmp_history->data);
            prompt->index = strlen(prompt->tmp_history->data);
            // if (prompt->tmp_history->next)
            //     prompt->tmp_history = prompt->tmp_history->next;
            break;
        }
    }
}

static void get_up_history(t_prompt *prompt) {
    while (prompt->tmp_history) {
        if (!mx_get_substr_index(prompt->tmp_history->data, prompt->tmp_command)) {
            strcpy(prompt->command, prompt->tmp_history->data);
            prompt->index = strlen(prompt->tmp_history->data);
            if (prompt->tmp_history->next)
                prompt->tmp_history = prompt->tmp_history->next;
            break;
        }
        prompt->tmp_history = prompt->tmp_history->next;
    }
}
