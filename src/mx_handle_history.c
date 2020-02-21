#include "ush.h"

static bool isvalid(t_prompt *prompt) {
    if (!mx_get_substr_index(prompt->tmp_history->data, prompt->tmp_command)
        && strcmp(prompt->tmp_history->data, prompt->command)
        && strcmp(prompt->tmp_history->data, prompt->tmp_command)) {
        return true;
    }
    return false;
}

static void get_down_history(t_prompt *prompt) {
    if (prompt->tmp_history)
        if (prompt->tmp_history->prev)
            prompt->tmp_history = prompt->tmp_history->prev;
    while (prompt->tmp_history) {
        if (isvalid(prompt)) {
            mx_rcmd(prompt->command, prompt->tmp_history->data,
                    sizeof(prompt->command), &prompt->index);
            break;
        }
        if (!prompt->tmp_history->prev) {
            prompt->end = true;
            break;
        }
        prompt->tmp_history = prompt->tmp_history->prev;
    }
    if (prompt->end) {
        mx_rcmd(prompt->command, prompt->tmp_command,
                sizeof(prompt->command), &prompt->index);
    }
}

static void get_up_history(t_prompt *prompt) {
    if (prompt->tmp_history
        && !strcmp(prompt->command, prompt->tmp_history->data)) {
        if (prompt->tmp_history->next)
            prompt->tmp_history = prompt->tmp_history->next;
    }
    while (prompt->tmp_history) {
        if (isvalid(prompt)) {
            mx_rcmd(prompt->command, prompt->tmp_history->data,
                    sizeof(prompt->command), &prompt->index);
            prompt->end = false;
            break;
        }
        if (!prompt->tmp_history->next)
            break;
        prompt->tmp_history = prompt->tmp_history->next;
    }
}

static void set_cursor(t_prompt *prompt) {
    prompt->index = strlen(prompt->command);
    prompt->cursor_index = strlen(prompt->command);
}

bool mx_handle_history(t_prompt *prompt) {
    if (!strcmp(prompt->buff, MX_DOWN_ARROW)) {
        get_down_history(prompt);
        set_cursor(prompt);
        return true;
    }
    if (!strcmp(prompt->buff, MX_UP_ARROW)) {
        get_up_history(prompt);
        set_cursor(prompt);
        return true;
    }
    return false;
}
