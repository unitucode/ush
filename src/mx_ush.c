#include "ush.h"

static void main_cycle();
static void init();
static void deinit();

int main() {
    init();
    main_cycle();
    deinit();
    system("leaks -q ush");
    return 0;
}

static void main_cycle() {
    int result = 0;
    t_prompt *prompt = malloc(sizeof(t_prompt));

    while (strcmp(prompt->command, "exit") && result != -1) {
        printf("%s> ", MX_SHELL_PROMPT);
        mx_get_input(prompt, &result);
        mx_update_history(prompt);
        printf("\r\n");
    }
    mx_d_del_list(&prompt->history_head);
    free(prompt);
}

static void deinit() {
    mx_disable_canon();
}

static void init() {
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}
