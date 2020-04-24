#include "ush.h"

void mx_home(t_map **map) {
    int result = chdir(getenv("HOME"));
    char *newdir = getenv("HOME");

    if (result < 0) {
        if (newdir == NULL)
            fprintf(stderr, "cd: HOME not set\n");
        else {
            fprintf(stderr, "cd: %s: ", newdir);
            perror("");
        }
        return;
    }
    mx_change_map(map, newdir);
}
