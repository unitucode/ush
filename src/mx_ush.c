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
    char cmd[ARG_MAX + 1];
    int result = 0;

    while (strcmp(cmd, "exit") && result != -1) {
        printf("%s> ", MX_SHELL_PROMPT);
        result = mx_get_input(cmd);
        printf("\r\n");
    }
}

static void deinit() {
    mx_disable_canon();
}

static void init() {
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}
