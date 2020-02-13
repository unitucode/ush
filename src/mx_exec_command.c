#include "ush.h"

static bool is_our_command(char *command) {
    if (strcmp(command, "pwd") == 0
        || strcmp(command, "cd") == 0
        || strcmp(command, "echo") == 0
        || strcmp(command, "unset") == 0
        || strcmp(command, "export") == 0
        || strcmp(command, "which") == 0) {
        return true;
    }
    return false;
}

static bool check_dir(char *path, char *file) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    bool retval = false;

    if (dir) {
        while ((entry = readdir(dir)) != NULL)
            if (strcmp(entry->d_name, file) == 0)
                retval = true;
        closedir(dir);
    }
    return retval;
}

static bool find_command(char *path, char *command, char **filename) {
    char **paths = mx_strsplit(path, ':');
    bool retval = false;
    char fname[PATH_MAX];

    if (paths) {
        for (int i = 0; paths[i]; i++)
            if (check_dir(paths[i], command)) {
                retval = true;
                sprintf(fname, "%s/%s", paths[i], command);
                *filename = strdup(fname);
                printf("FILENAME: %s\n", fname);
            }
        mx_del_strarr(&paths);
    }
    return retval;
}

static int exec_our(char *command, char **argv, int fd) {
    pid_t pid;

    if (strcmp(command, "unset") == 0)
        return mx_unset(++(argv));
    if (strcmp(command, "export") == 0)
        return mx_export(++(argv), fd);
    pid = fork();
    if (pid == 0) {
        if (strcmp(command, "pwd") == 0)
            exit(mx_pwd(++(argv), fd));
        if (strcmp(command, "cd") == 0)
            exit(mx_cd(++(argv)));
        if (strcmp(command, "echo") == 0)
            exit(mx_cd(++(argv)));
        if (strcmp(command, "which") == 0)
            exit(mx_which(++(argv), fd));
    }
    return -1;
}

void mx_exec_command(char **argv, int fd) {
    char *filename = NULL;

    if (is_our_command(argv[0]))
        exec_our(argv[0], argv, fd);
    else if (find_command(getenv("PATH"), argv[0], &filename)) {
        t_process *process = mx_create_process(fd);
        extern char **environ;

        mx_exec(process, filename, argv, environ);
        mx_strdel(&filename);
    }
    else
        fprintf(stderr, "%s: command not found: %s\n",
                MX_SHELL_NAME, argv[0]);
}
