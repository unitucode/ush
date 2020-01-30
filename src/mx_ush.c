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
    // char str[20] = "Hello";
    // char c = 'x';
    // memmove(str + 3, str + 2, strlen(str + 2));
    // str[2] = c;
    // printf("str = %s\n", str);

    while (strcmp(prompt->command, "exit") && result != -1) {
        mx_get_input(prompt, &result);
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
