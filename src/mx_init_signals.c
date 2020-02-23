#include "ush.h"

void mx_init_signals() {
    sigset_t mask;

    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
}
