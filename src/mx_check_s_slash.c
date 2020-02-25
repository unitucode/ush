#include "ush.h"

void mx_check_s_slash(char *newdir, t_map **map) {
    char *str = realpath(newdir, NULL);

    if (strcmp(newdir, str) == 0) {
        mx_change_dir(newdir, map, 1);
        mx_strdel(&str);
    }
    else {
        fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
        mx_strdel(&str);
    }
}
