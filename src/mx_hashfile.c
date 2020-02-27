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

static void print_hash(char *file, int fd) {
    int hash = 0;

    hash = mx_hash(file);
    for (int i = 0; i < 10; i++) {
        dprintf(fd, "%x", (hash + 42) % 99999999);
        hash /= 2;
    }
    dprintf(fd, "\n");
}

int mx_hashfile(char **args, int fd) {
    char *file = NULL;

    if (!check_args(args))
        return 1;
    file = mx_file_to_str(args[0]);
    if (file) {
        print_hash(file, fd);
        mx_strdel(&file);
        return 0;
    }
    else if (!strlen(file)) {
        fprintf(stderr, "hashfile: file is empty\n");
        return 1;
    }
    fprintf(stderr, "hashfile: %s\n", strerror(errno));
    return 1;
}
