#include "ush.h"

static char *get_flag_arg(char **args, int *flag_idx, int *retval, int *idx) {
    if (args[0][(*flag_idx) + 1] == '\0')
        if (args[1] == NULL)
            *retval = mx_print_env_error(args[0][*flag_idx], 1);
        else {
            *flag_idx = -1;
            (*idx)++;
            return strdup(args[1]);
        }
    else {
        int shift = (*flag_idx) + 1;

        *flag_idx = -1;
        return strdup(args[0] + shift);
    }
    return NULL;
}

static void delete_var(char **delname) {
    unsetenv(*delname);
    if (delname != NULL)
        mx_strdel(delname);
}

static int parse_flag(char **args, char **path, int *idx) {
    int retval = 0;

    for (int i = 1; args[0][i] != '\0'; i++) {
        if (args[0][i] == 'P') {
            if (*path != NULL)
                mx_strdel(path);
            *path = get_flag_arg(args, &i, &retval, idx);
        }
        else if (args[0][i] == 'u') {
            char *delname = get_flag_arg(args, &i, &retval, idx);

            delete_var(&delname);
        }
        else if (args[0][i] != 'i' && args[0][i] != '-')
            return mx_print_env_error(args[0][i], 0);
        if (retval || i == -1)
            break;
    }
    return retval;
}

static int parse_flags(char **argv, char **path, int *idx) {
    int retval = 0;
    bool flag_stop = 0;
    extern char **environ;

    for (*idx = 0; argv[*idx] && !flag_stop && !retval;) {
        if (argv[*idx][0] == '-' && mx_strcmp(argv[*idx], "--") != 0) {
            if (mx_match(argv[*idx], MX_ENV_FLAG_I))
                mx_clearenv();
            retval = parse_flag(&argv[*idx], path, idx);
        }
        else {
            if (mx_strcmp(argv[*idx], "--") != 0)
                (*idx)--;
            flag_stop = 1;
        }
        (*idx)++;
    }
    return retval;
}

static void parse_vars(char **argv, char **path, int *idx) {
    for (; argv[*idx]; (*idx)++) {
        if (mx_match(argv[*idx], "^.+=.*$"))
            mx_putenv(argv[*idx]);
        else
            break ;
    }
    if (mx_strcmp(*path, getenv("PATH") != 0) {
        *path = ;
    }
}

int mx_env(char **argv, int fd) {
    int retval = 0;
    extern char **environ;
    char **env = mx_env_copy();
    char *filename = NULL;
    int idx = 0;
    char *path = mx_strdup(getenv("PATH"));

    if (!(retval = parse_flags(argv, &path, &idx))) {
        parse_vars(argv, &path, &idx);
        if (argv[idx] == NULL)
            mx_print_env(fd);
        else if (mx_find_command(path, argv[idx], &filename)) {
            t_process *process = mx_create_process(fd);

            mx_exec(process, filename, &argv[idx], environ);
            mx_del_process(&process);
        }
        else {
            fprintf(stderr, "env: %s: No such file or directory\n", argv[idx]);
            retval = 127;
        }
    }
    mx_clearenv();
    mx_env_fill(env);
    mx_del_strarr(&env);
    mx_strdel(&path);
    mx_strdel(&filename);
    return retval;
}
/*
env {} (VARS) []         если аргументов нет - то вывод (переменных)
env {} () [ARGS]         если аругументы есть - то выполнение
env {-P}(Путь) (VARS) [] ожидание пути после '-P'
env {} (VARS) [ARGS]     после переменных могут быть только переменные или аргументы
*/
