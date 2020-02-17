#include "ush.h"

// void mx_handle_command(char *command, int *code) {
    // char **commands = mx_parse_command(command, code);
    // char **arguments = NULL;

    // if (*code || !commands)
    //     return;
    // for (unsigned int i = 0; commands[i]; i++) {
    //     if (!(arguments = mx_interpretate(commands[i], code))) {
    //         continue;
    //     }
    //     // printf("cmd---\n");
    //     // for (int j = 0; arguments[j]; j++) {
    //     //     printf("arg = (%s)\n", arguments[j]);
    //     // }
    //     // printf("cmd---\n");
    //     mx_exec_command(arguments, 1);
    //     mx_del_strarr(&arguments);
    // }
    // mx_del_strarr(&commands);
//     wordexp_t p;
//     char **w;
//     int fds[2];
//     int old;
//     size_t bytes = 0;
//     char buf[128];
//     old = dup(STDERR_FILENO);
//     pipe(fds);
//     dup2(fds[1], STDERR_FILENO);

//     int result = wordexp(command, &p, WRDE_SHOWERR);
//     close(fds[1]);
//     dup2(old, STDERR_FILENO);
//     while ((bytes = read(fds[0], buf, sizeof(buf) - 1)) > 0) {
//         buf[bytes] = '\0';
//         printf("buf = %s", buf);
//     }
//     close(fds[0]);
//     w = p.we_wordv;
//     if (result) {
//         *code = 1;
//         return;
//     }
//     if (!p.we_wordc) {
//         *code = 1;
//         return;
//     }
//     mx_exec_command(w, 1);
//     wordfree(&p);
// }


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

static void exec_command(char *command, int *code) {
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
        *code = 1;
        if (!word.we_wordc)
            wordfree(&word);
        return;
    }
    mx_exec_command(word.we_wordv, 1);
    wordfree(&word);
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
