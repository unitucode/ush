#include "ush.h"

static bool parse_flags(char **flags, bool *mode) {
    bool flag_stop = 0;

    for (int i = 0; flags[i]; i++) {
        if (flags[i][0] == '-' && !flag_stop) {
            flag_stop = mx_is_flag_stop(flags[i]);
            for (int j = 1; flags[i][j] != '\0'; j++)
                if (flags[i][j] == 'P')
                    *mode = 1;
                else if (flags[i][j] != 'L' && (flags[i][j] != '-'
                         || (flags[i][j] == '-' && j == 2))) {
                    fprintf(stderr, "pwd: bad option: -%c\n", flags[i][j]);
                    return 1;
                }
        }
        else {
            fprintf(stderr, "pwd: too many arguments\n");
            return 1;
        }
    }
    return 0;
}

int mx_pwd(char **flags, int fd) {
    t_map **map = mx_get_lenv();
    bool mode = 0;
    char *pwd = mx_get_map(map, "PWD");

    if (!parse_flags(flags, &mode)) {
        if (mode) {
            char *rpath = realpath(pwd, NULL);

            dprintf(fd, "%s\n", rpath);
            mx_strdel(&rpath);
        }
        else
            dprintf(fd, "%s\n", pwd);
        return 0;
    }
    return 1;
}

