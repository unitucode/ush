#include "ush.h"

static char *argv_to_str(char **argv) {
    char str[ARG_MAX] = "";

    for (unsigned int i = 0; argv[i]; i++) {
        strcat(str, argv[i]);
        if (argv[i + 1]) {
            strcat(str, " ");
        }
    }
    return strdup(str);
}

static bool run_process(t_process *process,
                        char *filename, char **argv, char **env) {
    process->cmd = argv_to_str(argv);
    process->status = posix_spawn(&process->pid, filename, &process->actions,
                                  &process->attrs, argv, env);
    process->gpid = getpgid(process->pid);
    tcsetpgrp(STDOUT_FILENO, process->gpid);
    if (process->status) {
        return false;
    }
    return true;
}

static void add_process(t_process *process) {
    t_list **list = mx_get_list_procs();
    t_list *tmp = *list;

    while (tmp) {
        if (!tmp->next) {
            break;
        }
        tmp = tmp->next;
    }
    mx_push_back(list, process);
    if (tmp)
        process->pos = ((t_process*)tmp->data)->pos + 1;
    else
        process->pos = 1;
    printf("[%d]    %d suspended  %s\n", process->pos, process->pid, 
           process->cmd);
}

int mx_exec(t_process *process, char *filename, char **argv, char **env) {
    int retval = 0;

    mx_disable_canon();
<<<<<<< HEAD
    process->status = posix_spawn(&process->pid, filename,
                         &process->actions, &process->attrs, argv, env);
    // waitpid(process->pid, &status, WUNTRACED);
    if (waitpid(process->pid, &process->status, WUNTRACED) != -1) {
        if (WIFSTOPPED(process->status)) {
            mx_push_back(list, process);
            outputList();
=======
    if (!run_process(process, filename, argv, env)) {
        fprintf(stderr, "%s: %s: %s\n", filename, strerror(process->status),
                MX_SHELL_NAME);
        retval = 126;
    }
    else if (waitpid(process->gpid, &process->status, WUNTRACED) != -1) {
        if (MX_WIFSTOPPED(process->status)) {
            add_process(process);
>>>>>>> f173e170b4415161bf33cd723bf2731273cfdd8e
        }
    }
    tcsetpgrp(STDOUT_FILENO, getpgrp());
    mx_enable_canon();
    return retval != 126 ? MX_WEXITSTATUS(process->status) : retval;
}
<<<<<<< HEAD

// static void test() { // create a new process;
//     mx_disable_canon();
//     extern char **environ;
//     pid_t pid;
//     sigset_t set;
//     char *argv[] = {"ls", "-R", "/", NULL};
//     int status;
//     sigemptyset(&set);
//     sigaddset(&set, SIGINT);
//     sigaddset(&set, SIGTSTP);
//     // sigfillset(&set);
//     posix_spawnattr_t attr;
//     posix_spawnattr_init(&attr);
//     posix_spawnattr_setsigdefault(&attr, &set);
//     posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSIGDEF | POSIX_SPAWN_SETSIGMASK);
//     status = posix_spawn(&pid, "/bin/ls", NULL, &a`ttr, argv, environ);
//     if (status) {
//         printf("ERROR: posix_spawn: %s\n", strerror(status));
//         exit(EXIT_FAILURE);
//     }
//     printf("PID: %i\n", pid);
//     if (waitpid(pid, &status, WUNTRACED) != -1) {
//         printf("EXIT: %i\n", status);
//         if (WIFSTOPPED(status)) {
//             //if ctrl+z
//         }
//     }
//     else {
//         perror("ERROR: waitpid");
//     }
//     mx_enable_canon();
// }
=======
>>>>>>> f173e170b4415161bf33cd723bf2731273cfdd8e
