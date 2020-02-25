#include "ush.h"

static bool check_dir(char *path, char *file) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    bool retval = 0;

    if (dir) {
        while ((entry = readdir(dir)) != NULL)
            if (!strcmp(entry->d_name, file) &&
                strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
                retval = 1;
        closedir(dir);
    }
    return retval;
}

static void check_in_abspath(char *command, char **filename, bool *retval) {
    char *dir_name = dirname(command);
    char *base_name = basename(command);

    if (check_dir(dir_name, base_name)) {
        *retval = 1;
        *filename = mx_strdup(command);
    }
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
                if (*filename)
                    mx_strdel(filename);
                *filename = strdup(fname);
            }
        mx_del_strarr(&paths);
    }
    if (!retval)
        check_in_abspath(command, filename, &retval);
    return retval;
}
