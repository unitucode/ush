#include "ush.h"

static void print_env_illop (char option) {
    fprintf(stderr, "env: illegal option -- %c\n", args[0][i]);
    fprintf(stderr, "usage: env [-i] [-P utilpath] [-u name]\n");
    fprintf(stderr, "\t\t   [name=value ...] [utility [argument ...]]\n");
}

static int parse_flag(char **args) {
    if (args[0][0] = '-') {
        for (int i = 1; args[0][i]; i++) {
            if (args[0][i] == 'P' || args[0][i] == 'u')
            else if (args[0][i] != 'i' || args[0][i] != '-') {
                print_env_illop(args[0][i]);
            }
        }
    }
    return 0;
}

static int parse_flags(char **argv, char **path, char ***environ) {
    bool flag_stop = 0;
    int i;

    *path = strdup(getenv("PATH"));
    for (i = 0; argv[i] && !flag_stop;) {
        if (!mx_strcmp(argv[i], "--"))
            flag_stop = 1;
        else {
            if (mx_match(argv[i], "^-(i*|i+.*|-.+)$"))
                mx_strdel(environ);
            parse_flag(&argv[i]);
        }
        i++;
    }
    return i;
}

int mx_env(char **argv, int fd) {
    extern char **environ;
    char **env = mx_env_copy(environ);
    // char *filename = NULL;
    int idx = 0;
    int retval = 0;
    char *path = NULL;
fd++;
    if ((idx = parse_flags(argv, &path, &environ)))
        printf("INDEX %d: %s\n", idx, argv[idx]);
    // printf("PATH: %s\n", path);
        // if (mx_find_command(path, argv[i], &filename)) {
        //     t_process *process = mx_create_process(fd);

        //     mx_exec(process, filename, argv, environ);
        //     mx_del_process(&process);
        // }
        // else {
        //     fprintf(stderr, "env: %s: No such file or directory\n", argv[i]);
        //     retval = 127;
        // }
    mx_del_strarr(&env);
    mx_strdel(&path);
    // mx_strdel(&filename);
    return retval;
}
/*
env {} (VARS) []         если аргументов нет - то вывод (переменных)
env {} () [ARGS]         если аругументы есть - то выполнение
env {-P}(Путь) (VARS) [] ожидание пути после '-P'
env {} (VARS) [ARGS]     после переменных могут быть только переменные или аргументы
*/
