#include "ush.h"

t_process *mx_create_process(int fd) {
    t_process *process = malloc(sizeof(t_process));

    sigemptyset(&process->signals);
    sigaddset(&process->signals, SIGINT);
    if (fd == 1)
        sigaddset(&process->signals, SIGTSTP);
    posix_spawnattr_init(&process->attrs);
    posix_spawnattr_setsigdefault(&process->attrs, &process->signals);
    posix_spawnattr_setflags(&process->attrs,
                             POSIX_SPAWN_SETSIGDEF | POSIX_SPAWN_SETSIGMASK);
    posix_spawn_file_actions_init(&process->actions);
    posix_spawn_file_actions_adddup2(&process->actions, fd, 1);
    return process;
}

// if (!strcmp(prompt->command, "ls")) {
//             char buff[1024];
//             size_t read_bytes = 0;
//             int fd[2];
//             pipe(fd);
//             t_process *process = mx_create_process(fd[1]);
//             char *args[] = {"-l", NULL};
//             mx_exec(process, "/bin/ls", args, environ);
//             read_bytes = read(fd[0], buff, sizeof(buff) - 1);
//             buff[read_bytes] = '\0';
//             printf("buff = %s\n", buff);
//         }

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
//     status = posix_spawn(&pid, "/bin/ls", NULL, &attr, argv, environ);
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
