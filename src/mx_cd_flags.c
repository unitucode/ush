#include "ush.h"

static bool check_link_full_path(t_map **map, char *newdir) {
    char *path = mx_strnew(mx_strlen(mx_get_map(map, "PWD"))
                           + 1 + mx_strlen(newdir));
    char *real_path;
    bool result = false;

    if (mx_check_dir_exists(newdir) == false) {
        mx_strdel(&path);
        return false;
    }
    path = strcpy(path, mx_get_map(map, "PWD"));
    path = strcat(path, "/");
    path = strcat(path, newdir);
    real_path = realpath(path, NULL);
    if (strcmp(path, real_path) != 0)
        result = true;
    mx_strdel(&real_path);
    mx_strdel(&path);
    return result;
}

static bool check_link_newdir(t_map **map, char *newdir) {
    char *pwd = mx_strjoin(mx_get_map(map, "PWD"), "/");
    char *real_pwd = realpath(pwd, NULL);
    char *path = mx_strnew(mx_strlen(real_pwd) + 1 + mx_strlen(newdir));
    char *real_path;
    bool result;

    path = strcpy(path, real_pwd);
    path = strcat(path, "/");
    path = strcat(path, newdir);
    mx_strdel(&pwd);
    mx_strdel(&real_pwd);
    real_path = realpath(path, NULL);
    path = mx_clear_slash_end(mx_parse_path(NULL, path, map));
    result = (mx_strcmp(path, real_path) == 0) ? false : true;
    mx_strdel(&path);
    mx_strdel(&real_path);
    return result;
}

static int cd_flag_s(t_map **map, char *newdir) {
    if (newdir == NULL)
        mx_change_dir(NULL, map, 1);
    else if (newdir[0] == '/') {
        if (mx_check_dir_exists(newdir) == false) {
            fprintf(stderr, "cd: %s: No such file or directory\n", newdir);
            return 0;
        }
        mx_check_s_slash(newdir, map);
    }
    else {
        if (check_link_newdir(map, newdir)) {
            fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
            return 0;
        }
        else
            mx_change_dir(newdir, map, 1);
    }
    return 1;
}

void mx_flag_p_full_path(t_map **map, char *newdir) {
    if (check_link_full_path(map, newdir)) {
        char *pwd = strdup(mx_get_map(map, "PWD"));
        char *path = mx_strnew(mx_strlen(pwd) + 1 + mx_strlen(newdir));
        char *real_path;

        path = strcpy(path, pwd);
        path = strcat(path, "/");
        path = strcat(path, newdir);
        real_path = realpath(path, NULL);
        chdir("/");
        chdir(real_path);
        mx_strdel(&pwd);
        mx_change_map(map, real_path);
        mx_put_pwd(real_path, mx_get_map(map, "OLDPWD"));
        mx_strdel(&path);
        mx_strdel(&real_path);
    }
    else
        mx_change_dir(newdir, map, 1);
}


void mx_cd_flags(char *flag, t_map **map, char *newdir) {
    if (strcmp(flag, "-Ps") == 0 || strcmp(flag, "-sP") == 0) {
        if (cd_flag_s(map, newdir) == 1)
            flag = "-P";
        newdir = ".";
    }
    if (strcmp(flag, "-P") == 0) {
        mx_flag_p_slash(newdir, map);
    }
    else if (strcmp(flag, "-s") == 0)
        cd_flag_s(map, newdir);
}
