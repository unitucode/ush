#include "ush.h"

void mx_env_fill(char **src) {
    for (int i = 0; src && src[i]; i++)
        mx_putenv(src[i]);
}
