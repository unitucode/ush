#include "ush.h"

void mx_disable_canon(void) {
    tcsetattr(STDIN_FILENO, TCSADRAIN, mx_get_tty());
}
