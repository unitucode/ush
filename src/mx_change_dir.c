#include "ush.h"

void mx_change_dir(char *newdir, t_map **map, int fd) {
    int result;

    if (newdir == NULL) {
        mx_home(map);
        return;
    }
    else if (!strcmp(newdir, "~OLDPWD")) {
        mx_oldpwd(newdir, map, fd);
        return;
    }
    result = chdir(newdir);
    if (result < 0) {
        fprintf(stderr, "cd: %s: ", newdir);
        perror("");
    }
    else
        mx_change_map(map, newdir);
}
