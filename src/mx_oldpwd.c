#include "ush.h"

void mx_oldpwd(char *newdir, t_map **map, int fd) {
    int result = chdir(mx_get_map(map, "OLDPWD"));
    
    if (result < 0) {
        fprintf(stderr, "cd: OLDPWD is NULL\n");
        return;
    }
    mx_change_map(map, newdir);
    dprintf(fd, "%s\n", mx_get_map(map, "OLDPWD"));
}


