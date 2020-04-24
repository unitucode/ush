#include "ush.h"

void mx_flag_p_slash(char *newdir, t_map **map) {
    if (newdir == NULL)
        mx_change_dir(newdir, map, 1);
    else if (newdir[0] == '/') {
        char *str = realpath(newdir, NULL);

        if (mx_check_dir_exists(newdir) == false) {
            fprintf(stderr, "cd: %s: No such file or directory\n", newdir);
            mx_strdel(&str);
        }
        else if (strcmp(newdir, str) == 0)
            mx_change_dir(newdir, map, 1);
        else
            mx_change_dir(str, map, 1);
        mx_strdel(&str);
    }
    else {
        mx_flag_p_full_path(map, newdir);
    }
}
