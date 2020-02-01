#include "ush.h"

static void change_dir(char *newdir, t_map **map);
static int check_on_flags(char *flag, char *newdir, t_map **map);
static void do_on_flags(int flag, char *newdir, t_map **map);
static void change_map(t_map **map, char *newdir);

int mx_cd(char **split, t_map **map) {
    if (split == NULL)
        change_dir(NULL, map);
    if (check_on_flags(split[0], split[1], map) == 0) {
        change_dir(split[0], map);
    }
    return 1;
}



static void change_dir(char *newdir, t_map **map) {
    int result;

    if (newdir == NULL)
        result = chdir(getenv("HOME"));
    else if (mx_strcmp(newdir, "~OLDPWD") == 0) {
        result = chdir(mx_get_map(map, "OLDPWD"));
        printf("%s\n", mx_get_map(map, "OLDPWD"));
    }
    else
        result = chdir(newdir);
    if (result < 0)
        fprintf(stderr, "cd: %s No such file or directory.\n", newdir);
    else {
        change_map(map, newdir);
    }
}

static int check_on_flags(char *flag, char *newdir, t_map **map) {
    if (mx_strcmp(flag, "-P") == 0)
        do_on_flags(1, newdir, map);
    else if (mx_strcmp(flag, "-s") == 0)
        do_on_flags(2, newdir, map);
    else if (mx_strcmp(flag, "-") == 0 && newdir == NULL)
        change_dir("~OLDPWD", map);
    else if ((mx_strcmp(flag, "-") == 0 && newdir != NULL)
            || flag[0] == '-')
        fprintf(stderr, "cd: string not in pwd: %s\n", flag); 
    else if (mx_strcmp(flag, "/") == 0)
        change_dir(flag, map);
    else
        return 0;
    return 1;
}

static void do_on_flags(int flag, char *newdir, t_map **map) {
    char *newdir_path;
    char *newdir_path_real;
    
    newdir_path = mx_strjoin(getenv("PWD"), "/");
    newdir_path = strcat(newdir_path, newdir);
    newdir_path_real = realpath(newdir_path, NULL);
    if (flag == 1) {
        if (mx_strcmp(newdir_path, newdir_path_real) != 0) {

        }
    }
    else if (flag == 2) {
        if (mx_strcmp(newdir_path, newdir_path_real) != 0)
            fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
        else
            change_dir(newdir, map);
    }
    mx_strdel(&newdir_path_real); 
    mx_strdel(&newdir_path);
}

static void change_map(t_map **map, char *newdir) {
    char *tmp = mx_strnew(mx_strlen(mx_get_map(map, "PWD")));
    char *result_path;
    
    if (mx_strcmp(newdir, "~OLDPWD") != 0) {
        tmp = mx_strcpy(tmp, mx_get_map(map, "PWD"));
        result_path = mx_parse_path(tmp, newdir, map);     
        mx_put_map(map, "OLDPWD", strdup(mx_get_map(map, "PWD")));            
        mx_put_map(map, "PWD", strdup(result_path));                          
        mx_strdel(&result_path);
        mx_strdel(&tmp);
    }
    else {
        mx_strdel(&tmp);
        tmp = strdup(mx_get_map(map, "OLDPWD"));
        mx_put_map(map, "OLDPWD", strdup(mx_get_map(map, "PWD")));
        mx_put_map(map, "PWD", tmp);
    }
}
