#include "ush.h"

void mx_print_env() {
    extern char **environ;

    for (int i = 0; environ[i]; i++)
        puts(environ[i]);
}
