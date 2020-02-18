#include "ush.h"

static void print_errors(int fd) {
    char *buff = mx_strnew(ARG_MAX);
    size_t line_cap = 0;
    ssize_t bytes = 0;
    FILE *fp = fdopen(fd, "r");

    while ((bytes = getdelim(&buff, &line_cap, '\n', fp)) != -1) {
        buff[bytes] = '\0';
        fprintf(stderr, "u%s", buff);
    }
    fclose(fp);
    close(fd);
    mx_strdel(&buff);
}

static void fork_command(char *command) {
    wordexp_t word;
    int result_code = 0;
    int fds[2];
    int old;

    pipe(fds);
    old = dup(STDERR_FILENO);
    dup2(fds[1], STDERR_FILENO);
    result_code = wordexp(command, &word, WRDE_SHOWERR);
    close(fds[1]);
    dup2(old, STDERR_FILENO);
    print_errors(fds[0]);
    if (result_code || !word.we_wordc) {
        if (!word.we_wordc)
            wordfree(&word);
        exit(result_code);
    }
    mx_exec_command(word.we_wordv, 1);
    wordfree(&word);
    exit(result_code);
}

static void exec_command(char *command, int *code) {
    int status = 0;
    sigset_t mask;
    pid_t child = fork();

    if (!child) {
        sigfillset(&mask);
        sigdelset(&mask, SIGINT);
        sigprocmask(SIG_SETMASK, &mask, NULL);
        mx_disable_canon();
        fork_command(command);
    }
    waitpid(child, &status, 0);
    mx_enable_canon();
    *code = status;
}

void mx_handle_command(char *command, int *code) {
    char **commands = mx_parse_command(command, code);
    unsigned int i = 0;

    if (*code || !commands)
        return;
    while (commands[i]) {
        exec_command(commands[i], code);
        i++;
    }
    mx_del_strarr(&commands);
}
