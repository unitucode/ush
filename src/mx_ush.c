#include "ush.h"

void mx_init(void) {
    mx_putenv("MX_PROMPT=u$h> ");
    mx_init_var_lists();
    mx_init_map_vars();
    mx_increment_shlvl();
    mx_var_list_insert(SHELL,
                       "PATH=/bin:/usr/bin:/usr/local/bin:/usr/sbin:/sbin");
    mx_init_signals();
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}

bool check_stdin(int *exit_code) {
    char *buff = NULL;
    size_t linecap = 0;
    ssize_t linelen = 0;

    if (isatty(STDIN_FILENO))
        return false;
    buff = mx_strnew(ARG_MAX + 1);
    while ((linelen = getline(&buff, &linecap, stdin)) > 0) {
        buff[linelen] = '\0';
        if (buff[linelen - 1] == '\n')
            buff[linelen - 1] = '\0';
        mx_handle_command(buff, exit_code);
    }
    mx_strdel(&buff);
    return true;
}

void mx_deinit(void) {
    mx_disable_canon();
    mx_kill_process();
    t_map **map = mx_get_lenv();
    mx_del_map(map);
}

static void main_cycle(void) {
    int result = 0;
    t_prompt *prompt = malloc(sizeof(t_prompt));
    extern char **environ;
    int fd = isatty(1) ? 1 : 2;

    if (!isatty(1) && !isatty(2))
        fd = open("/dev/null", O_RDONLY);
    while (result != -1) {
        mx_get_input(prompt, fd, &result);
        dprintf(fd, "\r\n");
        mx_handle_command(prompt->command, &result);
    }
    if (fd != 1 && fd != 2)
        close(fd);
    mx_d_del_list(&prompt->history_head);
    free(prompt);
}

int main(int argc, char **argv) {
    int exit_code = 0;

    if (argc > 1) {
        fprintf(stderr, "%s: illegal option -- %s\n", MX_SHELL_NAME, argv[1]);
        fprintf(stderr, "usage: %s ./ush\n", MX_SHELL_NAME);
        return 1;
    }
    mx_init();
    if (check_stdin(&exit_code)) {
        mx_deinit();
        exit(exit_code);
    }
    main_cycle();
    mx_deinit();
    system("leaks -q ush");
    return 0;
}
