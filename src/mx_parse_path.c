#include "ush.h"

static int count_size_of_path(char **split_path) {
    int size = 0;

    for (int i = 0; split_path[i]; i++) {
        if (!strcmp(split_path[i], ""))
            continue;
        for (int j = 0; split_path[i][j]; j++)
            size++;
        size++;
    }
    return size;
}

static char *collect_path(char **split_path) {
    int size = count_size_of_path(split_path);
    char *path = mx_strnew(size);
    bool null_path = true;

    for (int i = 0; split_path[i]; i++)
        if (strcmp(split_path[i], "") != 0)
            null_path = false;
    if (null_path) {
        mx_strdel(&path);
        return strdup("/");
    }
    path[0] = '/';
    for (int i = 0; split_path[i]; i++)
        if (strcmp(split_path[i], "") != 0) {
            path = strcat(path, split_path[i]);
            if (split_path[i + 1] != NULL)
                path = strcat(path, "/");
        }
    return path;
}

static char *check_path(char *path) {
    char **split_path = mx_strsplit(path, '/');
    char *result;
    
    for (int i = 0; split_path[i]; i++) {
        if (!strcmp(split_path[i], ".")) {
            mx_strdel(&split_path[i]);
            split_path[i] = strdup("");
        }
        if (!strcmp(split_path[i], ".."))
            mx_make_null_index(split_path, i);
    }
    result = collect_path(split_path);
    mx_del_strarr(&split_path);
    return result;
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

char *mx_parse_path(char *path, char *newdir, t_map **map) {
    char *temp;

    if (newdir == NULL)
        return strdup(getenv("HOME"));
    if (!strcmp(newdir, "/"))
        return strdup(newdir);
    if (!strcmp(newdir, "~OLDPWD"))
        return mx_get_map(map, "OLDPWD");
    if (newdir[0] == '/') {
        temp = check_path(newdir);
        return temp;
    }
    temp = make_bad_path(path, newdir);
    path = check_path(temp);
    mx_strdel(&temp);
    temp = mx_strndup(path, mx_strlen(path));
    mx_strdel(&path);
    return temp;
}
