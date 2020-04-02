#include "ush.h"

void mx_enable_canon(void) {
    struct termios tty;

    tcgetattr(STDIN_FILENO, mx_get_tty());
    tty = *mx_get_tty();
    tty.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSADRAIN, &tty);
}
