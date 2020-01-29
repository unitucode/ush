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
    if (prompt->tmp_history) {
        if (prompt->tmp_history->prev) {
            prompt->tmp_history = prompt->tmp_history->prev;
        }
        // else {
        //     strcpy(prompt->command, prompt->tmp_command);
        //     prompt->index = strlen(prompt->tmp_command);
        //     return;
        // }
    }
    while (prompt->tmp_history) {
        if (!mx_get_substr_index(prompt->tmp_history->data, prompt->tmp_command)
        && strcmp(prompt->tmp_history->data, prompt->tmp_command)) {
            strcpy(prompt->command, prompt->tmp_history->data);
            prompt->index = strlen(prompt->tmp_history->data);
            break;
        }
        if (!prompt->tmp_history->prev)
            break;
        prompt->tmp_history = prompt->tmp_history->prev;
    }
}

static void get_up_history(t_prompt *prompt) {
    if (prompt->tmp_history && !strcmp(prompt->command, prompt->tmp_history->data))
        if (prompt->tmp_history->next)
            prompt->tmp_history = prompt->tmp_history->next;
    while (prompt->tmp_history) {
        if (!mx_get_substr_index(prompt->tmp_history->data, prompt->tmp_command)
            && strcmp(prompt->tmp_history->data, prompt->tmp_command)) {
            strcpy(prompt->command, prompt->tmp_history->data);
            prompt->index = strlen(prompt->tmp_history->data);
            break;
        }
        if (!prompt->tmp_history->next)
            break;
        prompt->tmp_history = prompt->tmp_history->next;
    }
}
