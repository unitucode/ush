#include "ush.h"

void mx_print_env(int fd) {
    extern char **environ;

    for (int i = 0; environ[i]; i++)
        dprintf(fd, "%s\n", environ[i]);
}
