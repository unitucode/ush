#include "ush.h"

static bool check_args(char **args) {
    if (mx_arr_size(args) > 1) {
        fprintf(stderr, "hashfile: too many arguments\n");
        return false;
    }
    else if (!*args) {
        fprintf(stderr, "usage: hashfile [filename]\n");
        return false;
    }
    return true;
}

int mx_hashfile(char **args, int fd) {
    int hash = 0;
    char *file = NULL;
    char *hex = NULL;

    if (!check_args(args))
        return 1;
    file = mx_file_to_str(args[0]);
    if (file) {
        hash = mx_hash(file);
        for (int i = 0; i < 4; i++) {
            hex = mx_nbr_to_hex(hash / (i + 1));
            dprintf(fd, "%s", hex);
            mx_strdel(&hex);
        }
        printf("\n");
        mx_strdel(&file);
        return 0;
    }
    fprintf(stderr, "hashfile: %s\n", strerror(errno));
    return 1;
}
