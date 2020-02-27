#include "ush.h"

static bool check_args(char **args) {
    if (mx_arr_size(args) != 1) {
        fprintf(stderr, "usage: keygen [len]\n");
        return false;
    }
    if (strlen(args[0]) > 3) {
        fprintf(stderr, "keygen: too large len\n");
        return false;
    }
    for (unsigned int i = 0; i < strlen(args[0]); i++) {
        if (!isnumber(args[0][i])) {
            return false;
        }
    }
    return true;
}

int mx_keygen(char **args, int fd) {
    unsigned int random = 0;
    int times = 0;

    if (!check_args(args))
        return 1;
    times = atoi(args[0]);
    srand(time(0));
    random = rand();
    for (int i = 0; i < times; i++) {
        dprintf(fd, "%c", random % 42 + 48);
        random = 42 + mx_hash(&random) / mx_hash(&times) + random;
    }
    dprintf(fd, "\n");
    return 0;
}
