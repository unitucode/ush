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
    else
        result = chdir(newdir);
    if (result < 0) {
        fprintf(stderr, "cd: %s: ", newdir);
        perror("");
    }
    else
        mx_change_map(map, newdir);
}

void mx_change_map(t_map **map, char *newdir) {
    char *tmp = mx_strnew(mx_strlen(mx_get_map(map, "PWD")));
    char *result_path;

    if (strcmp(newdir, "~OLDPWD") != 0) {
        tmp = mx_strcpy(tmp, mx_get_map(map, "PWD"));
        result_path = mx_parse_path(tmp, newdir, map);
        mx_put_map(map, "OLDPWD", strdup(mx_get_map(map, "PWD")));
        mx_put_map(map, "PWD", strdup(result_path));
        mx_put_pwd(result_path, mx_get_map(map, "OLDPWD"));
        mx_strdel(&result_path);
        mx_strdel(&tmp);
    }
    else {
        mx_strdel(&tmp);
        tmp = strdup(mx_get_map(map, "OLDPWD"));
        mx_put_map(map, "OLDPWD", strdup(mx_get_map(map, "PWD")));
        mx_put_map(map, "PWD", tmp);
        mx_put_pwd(tmp, mx_get_map(map, "OLDPWD"));
    }
}
