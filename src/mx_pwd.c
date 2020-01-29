#include "ush.h"

static bool parse_flags(char **flags, bool *mode);
static bool is_flag_stop(char *flag);

int mx_pwd(char **flags) {
    t_map *map = mx_get_lenv();
    bool mode = 0;

    if (!parse_flags(flags, &mode))
    {
        if (mode)
            puts(getcwd(mx_get_map(&map, "PWD"), PATH_MAX));
        else
            puts(mx_get_map(&map, "PWD"));
        return 0;
    }
    return 1;
}

// parse_flags return 1 if any error cases, else 0
static bool parse_flags(char **flags, bool *mode) {
    bool flag_stop = 0;

    for (int i = 0; flags[i]; i++) {
        if (flags[i][0] == '-' && !flag_stop) {
            flag_stop = is_flag_stop(flags[i]);
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

static bool is_flag_stop(char *flag) {
    if ((flag[1] == '-' && flag[2] == '\0') || flag[1] == '\0')
    {
        return 1;
    }
    return 0;
}
// t_map *map = mx_get_lenv();
// mx_put_map(&map, "PWD", strdup(getenv("PWD")));

// t_map *map = mx_get_lenv();

// mx_get_map(&map, "PWD");
