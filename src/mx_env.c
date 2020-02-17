#include "ush.h"

static int print_env_error (char option, bool error) {
    if (error == 0)
        fprintf(stderr, "env: illegal option -- %c\n", option);
    if (error == 1)
        fprintf(stderr, "env: option requires an argument -- %c\n", option);
    fprintf(stderr, "usage: env [-i] [-P utilpath] [-u name]\n");
    fprintf(stderr, "           [name=value ...] [utility [argument ...]]\n");
    return 1;
}

static char *get_flag_arg(char **args, int flag_idx, int *retval, int *idx) {
    if (args[0][flag_idx + 1] == '\0')
        if (args[1] == NULL)
            *retval = print_env_error(args[0][flag_idx], 1);
        else {
            *idx = 1;
            return strdup(args[1]);
        }
    else {
        *idx = 1;
        return strdup(args[0]/*  + flag_idx + 1 */);
    }
    return NULL;
}

static int parse_flag(char **args, char **path, int *idx) {
    int retval = 0;
    int idx_inc = 0;

    if (args[0][0] == '-')
        for (int i = 1; args[0][i] != '\0'; i++) {
            if (args[0][i] == 'P')
                *path = get_flag_arg(args, i, &retval, &idx_inc);
            else if (args[0][i] == 'u') {
                char *delname = get_flag_arg(args, i, &retval, &idx_inc);

                unsetenv(delname);
                if (delname != NULL)
                    mx_strdel(&delname);
            }
            else if (args[0][i] != 'i' || args[0][i] != '-')
                return print_env_error(args[0][i], 0);
            if (idx_inc == 1)
                break;
        }
    *idx += idx_inc;
    return retval;
}

static int parse_flags(char **argv, char **path, int *idx) {
    int retval = 0;
    bool flag_stop = 0;
    extern char **environ;

    *path = strdup(getenv("PATH"));
    for (*idx = 0; argv[*idx] && !flag_stop;) {
        if (!mx_strcmp(argv[*idx], "--"))
            flag_stop = 1;
        else {
            if (mx_match(argv[*idx], MX_ENV_FLAG_I))
                mx_del_strarr(&environ);
            retval = parse_flag(&argv[*idx], path, idx);
        }
        (*idx)++;
    }
    return retval;
}

int mx_env(char **argv, int fd) {
    int retval = 0;
    extern char **environ;
    char **env = mx_env_copy(environ);
    // char *filename = NULL;
    int idx = 0;
    char *path = NULL;
fd++;
    if (!(retval = parse_flags(argv, &path, &idx)))
        printf("INDEX %d: %s\n", idx, argv[idx]);
        printf("PATH: %s\n", path);
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
