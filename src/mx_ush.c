#include "ush.h"

static void main_cycle();

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

static void main_cycle() {
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

void mx_deinit() {
    mx_disable_canon();
    t_map **map = mx_get_lenv();
    mx_del_map(map);
}

void mx_init() {
    mx_init_var_lists();
    t_map **map = mx_get_lenv();
    char path[PATH_MAX];
    *map = mx_create_map(40);

    getcwd(path, sizeof(path));
    mx_put_map(map, strdup("OLDPWD"), strdup(getenv("OLDPWD")));
    mx_put_map(map, strdup("PWD"), strdup(getenv("PWD")));
    mx_put_map(map, strdup("?"), strdup("0"));
    mx_put_map(map, strdup("#"), strdup("0"));
    mx_put_map(map, strdup("0"), strdup(MX_SHELL_NAME));
    mx_put_map(map, strdup("_"), strdup(path));
    mx_put_map(map, strdup("$"), mx_itoa(getpid()));
    mx_put_map(map, strdup("*"), strdup(""));
    mx_put_map(map, strdup("@"), strdup(""));
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    char *args[3] = {"MX_PROMPT=ush> ", NULL};
    mx_export(args, 1);
    mx_increment_shlvl();
    mx_var_list_insert(SHELL,
                       "PATH=/bin:/usr/bin:/usr/local/bin:/usr/sbin:/sbin");
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}
