#include "ush.h"

static bool check_dir(char *path, char *file) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    bool retval = 0;

    if (dir) {
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, file) == 0)
                retval = 1;
        closedir(dir);
    }
    return retval;
}

bool mx_find_command(char *path, char *command, char **filename) {
    char **paths = mx_strsplit(path, ':');
    bool retval = 0;
    char fname[PATH_MAX];

    if (paths) {
        for (int i = 0; paths[i]; i++)
            if (check_dir(paths[i], command)) {
                retval = 1;
                sprintf(fname, "%s/%s", paths[i], command);
                *filename = strdup(fname);
            }
        mx_del_strarr(&paths);
    }
    return retval;
}
