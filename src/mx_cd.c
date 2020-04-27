#include "ush.h"

static int check_on_flags(char *flag, char *newdir, t_map **map, int fd) {
    if (!strcmp(flag, "-P") || !strcmp(flag, "-sP") || !strcmp(flag, "-Ps"))
        mx_cd_flags(flag, map, newdir);
    else if (!strcmp(flag, "-s"))
        mx_cd_flags("-s", map, newdir);
    else if (!strcmp(flag, "-") && newdir == NULL)
        mx_change_dir("~OLDPWD", map, fd);
    else if ((!strcmp(flag, "-") && newdir != NULL)
             || (flag[0] == '-' && newdir != NULL)) {
        fprintf(stderr, "cd: string not in pwd: %s\n", flag);
    }
    else if (!strcmp(flag, "/"))
        mx_change_dir(flag, map, 1);
    else
        return 0;
    return 1;
}

int mx_cd(char **split, int fd) {
    t_map **map = mx_get_lenv();

    if (!mx_arr_size(split))
        mx_change_dir(NULL, map, fd);
    else if (!check_on_flags(split[0], split[1], map, fd))
        mx_change_dir(split[0], map, fd);
    return 1;
}
