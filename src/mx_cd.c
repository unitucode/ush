#include "ush.h"

static int check_on_flags(char *flag, char *newdir, t_map **map) {
    if (strcmp(flag, "-P") == 0 || strcmp(flag, "-sP") == 0 ||
    strcmp(flag, "-Ps") == 0)
        mx_cd_flags(flag, map, newdir);
    else if (strcmp(flag, "-s") == 0)
        mx_cd_flags("-s", map, newdir);
    else if (strcmp(flag, "-") == 0 && newdir == NULL)
        mx_change_dir("~OLDPWD", map);
    else if ((strcmp(flag, "-") == 0 && newdir != NULL)
            || (flag[0] == '-' && newdir != NULL))
        fprintf(stderr, "cd: string not in pwd: %s\n", flag); 
    else if (strcmp(flag, "/") == 0)
        mx_change_dir(flag, map);
    else
        return 0;
    return 1;
}

int mx_cd(char **split) {
    t_map **map = mx_get_lenv();

    if (!mx_arr_size(split))
        mx_change_dir(NULL, map);
    else if (strcmp(split[0], "-P") == 0 || strcmp(split[0], "-s") == 0) {
        if (chdir(split[1]) != 0) {
            mx_change_dir(split[1], map);
            return 0;
        }
        else
            chdir("..");
    }
    else if (check_on_flags(split[0], split[1], map) == 0) {
        mx_change_dir(split[0], map);
    }
    return 1;
}



void mx_change_dir(char *newdir, t_map **map) {
    int result;

    if (newdir == NULL) {
        result = chdir(getenv("HOME"));
        newdir = getenv("HOME");
    }
    else if (strcmp(newdir, "~OLDPWD") == 0) {
        result = chdir(mx_get_map(map, "OLDPWD"));
        printf("%s\n", mx_get_map(map, "OLDPWD"));
    }
    else
        result = chdir(newdir);
    if (result < 0) {
        fprintf(stderr, "cd: %s", newdir);
        perror(" ");
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
