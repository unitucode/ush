#include "ush.h"

static bool search_exe(char *file, int mode);
static bool check_dir(char *path, char *file);
static int parse_flags(char **flags, int *mode);

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

static bool search_exe(char *file, int mode) {
    char **paths = mx_strsplit(getenv("PATH"), ':');
    bool retval = 1;

    for (int i = 0; paths[i]; i++)
        if(check_dir(paths[i], file)) {
            if (mode != 2)
                printf("%s/%s\n", paths[i], file);
            retval = 0;
            if (mode == 0)
                return 0;
        }
    if (retval)
        fprintf(stderr, "%s not found\n", file);
    return retval;
}

static bool check_dir(char *path, char *file) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir)
        while ((entry = readdir(dir)) != NULL)
            if (entry->d_type == DT_REG
                && strcmp(entry->d_name, file) == 0) {
                return 1;
            }
    return 0;
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
