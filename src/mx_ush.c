#include "ush.h"

void mx_init(void) {
    mx_putenv("MX_PROMPT=ush> ");
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

    while (result != -1) {
        mx_get_input(prompt, &result);
        printf("\r\n");
        mx_handle_command(prompt->command, &result);
    }
    mx_d_del_list(&prompt->history_head);
    free(prompt);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "%s: illegal option -- %s\n", MX_SHELL_NAME, argv[1]);
        fprintf(stderr, "usage: %s ./ush\n", MX_SHELL_NAME);
        return 1;
    }
    mx_init();
    main_cycle();
    mx_deinit();
    system("leaks -q ush");
    return 0;
}
