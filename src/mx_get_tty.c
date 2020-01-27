#include "ush.h"

struct termios *mx_get_tty() {
    static struct termios tty;

    return &tty;
}
