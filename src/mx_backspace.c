#include "ush.h"

void mx_backspace(unsigned int times, int fd) {
    for (unsigned int i = 0; i < times; i++)
        dprintf(fd, "\b\x1b[0K");
}
