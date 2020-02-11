#include "ush.h"

static bool type_check(struct dirent *entry, char *path) {
    char abs_path[PATH_MAX];

    sprintf(abs_path, "%s/%s", path, entry->d_name);
    if (entry->d_type == DT_REG)
        return 1;
    else if (entry->d_type == DT_LNK) {
        char *abs_real_path = realpath(abs_path, NULL);
        struct stat buff;

        stat(abs_real_path, &buff);
        mx_strdel(&abs_real_path);
        return MX_ISREG(buff.st_mode);
    }
    return 0;
}

static bool check_dir(char *path, char *file) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir)
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, file) == 0)
                if (type_check(entry, path)) {
                    closedir(dir);
                    return 1;
                }
    closedir(dir);
    return 0;
}

static bool search_exe(char *file, int mode) {
    char **paths = mx_strsplit(getenv("PATH"), ':');
    bool retval = 1;

    if (paths) {
        for (int i = 0; paths[i]; i++)
            if (check_dir(paths[i], file)) {
                if (mode != 2)
                    printf("%s/%s\n", paths[i], file);
                retval = 0;
                if (mode == 0) {
                    mx_del_strarr(&paths);
                    return 0;
                }
            }
        if (retval)
            fprintf(stderr, "%s not found\n", file);
        mx_del_strarr(&paths);
    }
    return retval;
}

static int parse_flags(char **flags, int *mode) {
    bool flag_stop = 0;
    int i;  // index of first non-flag argument

    for (i = 0; flags[i] && flags[i][0] == '-' && !flag_stop; i++) {
        flag_stop = mx_is_flag_stop(flags[i]);
        for (int j = 1; flags[i][j] != '\0'; j++)
            if (flags[i][j] == 's')
                *mode = 2;
            else if (flags[i][j] == 'a' && *mode != 2)
                *mode = 1;
            else if (flags[i][j] != '-'
                     || (flags[i][j] == '-' && j == 2)) {
                fprintf(stderr, "which: bad option: -%c\n", flags[i][j]);
                return -1;
            }
    }
    if (flags[i] == NULL)
        return -1;
    return i;
}

int mx_which(char **args) {
    bool end_status = 0;
    int mode = 0;
    int first_arg_index = parse_flags(args, &mode);

    if (first_arg_index != -1)
        for (int i = first_arg_index; args[i]; i++)
            end_status = end_status | search_exe(args[i], mode);
    else
        end_status = 1;
    return end_status;
}
