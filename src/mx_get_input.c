#include "ush.h"

static bool isvalid(char c);
static int get_code(char c);

int mx_get_input(char *buf) {
    char tmp[1];
    size_t index = 0;

    buf[0] = '\0';  
    while (read(STDIN_FILENO, tmp, 1) && isvalid(tmp[0])
           && index < ARG_MAX) {
        if (tmp[0] == 127 && index > 0) {
            printf("\b \b");
            index--;
        }
        else if (tmp[0] != 127) {
            buf[index++] = tmp[0];
            buf[index] = '\0';
            printf("%c", tmp[0]);
        }
    }
    return get_code(tmp[0]);
}

static int get_code(char c) {
    if (c == 3)
        return 130;
    if (c == 4)
        return -1;
    return 0;
}

static bool isvalid(char c) {
    if (c == 3 || c == '\n' || c == 4) {
        return false;
    }
    return true;
}
