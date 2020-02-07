#include "ush.h"

static char *check_path(char *path);
static char *make_bad_path(char *path, char *newdir);
static char *collect_path(char **split_path);
static int count_size_of_path(char **split_path);

char *mx_parse_path(char *path, char *newdir, t_map **map) {
    char *temp;
    
    if (newdir == NULL)
        return strdup(getenv("HOME"));
    if (mx_strcmp(newdir, "/") == 0)
        return strdup(newdir);
    if (mx_strcmp(newdir, "~OLDPWD") == 0)
        return mx_get_map(map, "OLDPWD");
    if (newdir[0] == '/')
        return mx_clear_slashes_end(newdir);
    temp = make_bad_path(path, newdir);
    path = check_path(temp);
    mx_strdel(&temp);
    return path;
}

static char *check_path(char *path) {
    char **split_path = mx_strsplit(path, '/');
    char *result;

    for (int i = 0; split_path[i]; i++) {
        if (mx_strcmp(split_path[i], ".") == 0) {
            mx_strdel(&split_path[i]);
            split_path[i] = strdup("null0");
        }
        if (mx_strcmp(split_path[i], "..") == 0) {
            mx_strdel(&split_path[i]);
            if (i > 0) {
                mx_strdel(&split_path[i - 1]);
                split_path[i - 1] = strdup("null0");
            }
            split_path[i] = strdup("null0");
        }
    }
    result = collect_path(split_path);
    mx_del_strarr(&split_path);
    return result;
}

static char *collect_path(char **split_path) {
    int size = count_size_of_path(split_path);
    char *path = mx_strnew(size);
    bool null_path = true;

    for (int i = 0; split_path[i]; i++)
        if (strcmp(split_path[i], "null0") != 0)
            null_path = false;
    if (null_path) {
        mx_strdel(&path);
        return strdup("/");
    }
    path[0] = '/';
    for (int i = 0; split_path[i]; i++) {
        if (strcmp(split_path[i], "null0") != 0) {
        path = strcat(path, split_path[i]);
        if (split_path[i + 1] && mx_strcmp(split_path[i + 1], "null0") != 0)
            path = strcat(path, "/");
        }
    }
    return path;
}

static int count_size_of_path(char **split_path) {
    int size = 0;
    
    for (int i = 0; split_path[i]; i++) {
        if (strcmp(split_path[i], "null0") == 0)
            continue;
        for (int j = 0; split_path[i][j]; j++)
            size++;
    size++;
    }
    return size;
}

static char *make_bad_path(char *path, char *newdir) {
    int newdir_slash;
    int path_slash;
    char *temp;

    (newdir[0] == '/') ? newdir_slash = 1 : 0;
    for (int i = 0; path[i]; i++)
        path_slash = (path[i] == '/') ? 1 : 0;
    if (path_slash == 1 && newdir_slash == 1) {
        newdir++;
        return mx_strjoin(path, newdir);
    }
    if (path_slash != 1 && newdir_slash != 1) {
        temp = mx_strjoin(path, "/");
        path = mx_strjoin(temp, newdir);
        mx_strdel(&temp);
        return path;
    }
    return mx_strjoin(path, newdir);
}
