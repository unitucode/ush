#include "ush.h"

void mx_change_map(t_map **map, char *newdir) {
    char *tmp = mx_strnew(mx_strlen(mx_get_map(map, "PWD")));
    char *result_path;

    if (strcmp(newdir, "~OLDPWD") != 0) {
        tmp = mx_strcpy(tmp, mx_get_map(map, "PWD"));
        result_path = mx_parse_path(tmp, newdir, map);
        result_path = mx_clear_slash_end(result_path);
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
