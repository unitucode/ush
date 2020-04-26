#include "ush.h"

void mx_oldpwd(char *newdir, t_map **map, int fd) {
    char *str = strdup(mx_get_map(map, "OLDPWD"));
    int result = chdir(str);

    if (result < 0) {
        if (!strcmp(str, ""))
            fprintf(stderr, "cd: OLDPWD not set\n");
        else {
            fprintf(stderr, "cd: %s: ", newdir);
            perror("");
        }
        mx_strdel(&str);
        return;
    }
    if (isatty(STDIN_FILENO))
        dprintf(fd, "%s\n", mx_get_map(map, "OLDPWD"));
    mx_change_map(map, newdir);
    mx_strdel(&str);
}
