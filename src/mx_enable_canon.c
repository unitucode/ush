#include "ush.h"

void mx_enable_canon() {
    struct termios tty;

    tcgetattr(STDIN_FILENO, &tty);
    tty.c_lflag &= ~(ICANON | ISIG | ECHO | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &tty);
}
