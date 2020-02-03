#include "ush.h"

void mx_print_env() {
    extern char **environ;

    for (int i = 0; environ[i]; i++) {
        mx_printstr(environ[i]);
        if (environ[i + 1] != NULL)
            mx_printstr("\n");
    }
}
