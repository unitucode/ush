#include "ush.h"

void mx_init_signals(void) {
    sigset_t mask;

    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
}
