#include "ush.h"

struct termios *mx_get_tty(void) {
    static struct termios tty;

    return &tty;
}
