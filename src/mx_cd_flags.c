#include "ush.h"

static bool check_link_newdir(t_map **map, char *newdir);
static void cd_flag_s(t_map **map, char *newdir);
static void flag_p_full_path(t_map **map, char *newdir);
static bool check_link_full_path(t_map **map, char *newdir);

void mx_cd_flags(char *flag, t_map **map, char *newdir) {
    if (strcmp(flag, "-P") == 0) {
        if (newdir == NULL)
            mx_change_dir(newdir, map);
        else if (newdir[0] == '/') {
            if (strcmp(newdir, realpath(newdir, NULL)) == 0)
                mx_change_dir(newdir, map);
            else
                mx_change_dir(realpath(newdir, NULL), map);
        }
        else
            flag_p_full_path(map, newdir); 
        }
    if (strcmp(flag, "-s") == 0)
        cd_flag_s(map, newdir);
}

static bool check_link_full_path(t_map **map, char *newdir) {
    char *path = mx_strnew(mx_strlen(mx_get_map(map, "PWD")) +
            1 + mx_strlen(newdir));
    char *real_path;
    
    /*if (chdir(newdir) != 0 && newdir != NULL) {
        mx_strdel(&path);
        return false;
    }*/
    path = strcpy(path, mx_get_map(map, "PWD"));
    path = strcat(path, "/");
    path = strcat(path, newdir);
    real_path = realpath(path, NULL);
    if (strcmp(path, real_path) != 0) {
        mx_strdel(&real_path);
        mx_strdel(&path);
        return true;
    }
    mx_strdel(&real_path);
    mx_strdel(&path);
    return false;
}

static void flag_p_full_path(t_map **map, char *newdir) {
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
        mx_strdel(&path);
        mx_strdel(&real_path);
    }
    else
        mx_change_dir(newdir, map);
}

static void cd_flag_s(t_map **map, char *newdir) {
    if (newdir == NULL)
        mx_change_dir(NULL, map);
    else if (newdir[0] == '/') {
        if (strcmp(newdir, realpath(newdir, NULL)) == 0)
            mx_change_dir(newdir, map);
        else
            fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
    }
    else {
        if (check_link_newdir(map, newdir))
            fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
        else
            mx_change_dir(newdir, map);
    }
}

static bool check_link_newdir(t_map **map, char *newdir) {
    char *pwd = mx_strjoin(mx_get_map(map, "PWD"), "/");
    char *real_pwd = realpath(pwd, NULL);
    char *path = mx_strnew(mx_strlen(real_pwd) + 1 + mx_strlen(newdir));
    char *real_path;
    bool result;

    path = mx_strcpy(path, real_pwd);
    path = mx_strcat(path, "/");
    path = mx_strcat(path, newdir);
    mx_strdel(&pwd);
    mx_strdel(&real_pwd);
    real_path = realpath(path, NULL);
    result = (mx_strcmp(path, real_path) == 0) ? false : true;
    mx_strdel(&path);
    mx_strdel(&real_path);
    return result;
}
