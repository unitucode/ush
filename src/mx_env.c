#include "ush.h"

static void env_deinit(char ***env, char **path, char **filename) {
    mx_clearenv();
    mx_env_fill(*env);
    mx_del_strarr(env);
    mx_strdel(path);
    mx_strdel(filename);
}

static void exec_process(char *filename, char **argv, int fd) {
    extern char **environ;
    t_process *process = mx_create_process(fd);

    printf("EXIT_STATUS: %d\n", mx_exec(process, filename, argv, environ));
    mx_del_process(&process);
}

int mx_env(char **argv, int fd) {
    char **env = mx_env_copy();
    char *filename = NULL;
    char *path = NULL;
    int retval = 0;
    int i = 0;

    if (!(retval = mx_env_parse_flags(argv, &path, &i))) {
        mx_env_parse_vars(argv, &path, &i, env);
        if (argv[i] == NULL)
            mx_print_env(fd);
        else if (mx_find_command(path, argv[i], &filename)) {
            puts("WORK");
            exec_process(filename, &argv[i], fd);
        }
        else {
            fprintf(stderr, "env: %s: No such file or directory\n", argv[i]);
            retval = 127;
        }
    }
    env_deinit(&env, &path, &filename);
    return retval;
}
