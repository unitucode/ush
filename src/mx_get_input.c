#include "ush.h"

// static bool isvalid(char *c, int index);
// static void backspace(size_t *index, int times);
// static void set_code(char *tmp, int *code, int index);

static void set_code(char *buff, int *code, int index);
static bool handle_key(t_prompt *prompt, int *code);
static void clear_prompt(t_prompt *prompt);

void mx_get_input(t_prompt *prompt, int *code) {
    clear_prompt(prompt);
    while (read(STDIN_FILENO, prompt->buff, 4)
           && prompt->index < ARG_MAX
           && handle_key(prompt, code)) {
        // if (isprint(prompt->buff[0]) && strlen(prompt->buff) == 1)
        //     prompt->command[prompt->index++] = prompt->buff[0];
        // else
        //     handle_key(prompt);
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
    // mx_handle_arrows(prompt);
    mx_handle_print_char(prompt);
    set_code(prompt->buff, code, prompt->index);
    memset(prompt->buff, '\0', sizeof(prompt->buff));
    return true;
}

static void clear_prompt(t_prompt *prompt) {
    memset(prompt->command, '\0', sizeof(prompt->command));
    prompt->index = 0;
    prompt->cursor_index = 0;
}

// void mx_get_input(char *buf, int *code) {
//     char tmp[4] = "";
//     size_t index = 0;

//     buf[0] = '\0';  
//     while (read(STDIN_FILENO, tmp, 5)
//            && index < ARG_MAX && isvalid(tmp, index)) {
//         if (tmp[0] == 0x7f && index > 0)
//             backspace(&index, 1);
//         if (tmp[0] == 0x15)
//             backspace(&index, index);
//         if (isprint(tmp[0]) && strlen(tmp) == 1) {
//             buf[index++] = tmp[0];
//             buf[index] = '\0';
//             printf("%c", tmp[0]);
//         }
//         fflush(stdin);
//         memset(tmp, '\0', sizeof(tmp));
//     }
//     set_code(tmp, code, index);
// }


// static void backspace(size_t *index, int times) {
//     for (int i = 0; i < times; i++) {
//         printf("\b \b");
//         (*index)--;
//     }
// }

// static bool isvalid(char *c, int index) {
//     if (c[0] == '\x04' && !index) {
//         return false;
//     }
//     if (mx_match(c, MX_NON_PRINTABLE)) {
//         return false;
//     }
//     return true;
// }
