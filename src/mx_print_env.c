#include "ush.h"

void mx_print_env() {
    extern char **environ;
    int len;

    for (len = 0; environ[len]; len++) {
    }
    mx_bubble_sort(environ, len);
    mx_print_strarr(environ, "\n");
}
