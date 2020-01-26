#include "ush.h"

static void main_cycle();
static void init();

int main() {
    init();
    main_cycle();
    return 0;
}

static void main_cycle() {
    char cmd[ARG_MAX + 1];
    int result = 0;

    while (strcmp(cmd, "exit") && result != -1) {
        printf("%s>> ", MX_SHELL_PROMPT);
        result = mx_get_input(cmd);
        printf("\r\n");
    }
}

static void init() {
    // sigset_t mask;
    struct termios tty;

    setvbuf(stdout, NULL, _IONBF, 0);
    // signal(SIGINT, SIG_IGN);
    // sigfillset(&mask);
    // sigprocmask(SIG_SETMASK, &mask, NULL);
    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ISIG | ECHO | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}
