#include "ush.h"
// #include <paths.h>

// static void test();
static void main_cycle();
static void init();
static void deinit();

int main(int argc, char **argv) {
    if (argc > 1) {
        fprintf(stderr, "%s: illegal option -- %s\n", MX_SHELL_NAME, argv[1]);
        fprintf(stderr, "usage: %s ./ush\n", MX_SHELL_NAME);
        return 1;
    }
    init();
    // test();
    main_cycle();
    deinit();
    // setvbuf(stdout, NULL, _IONBF, 0);
    // char *argv[20] = {"-e", "-ne\x0a", NULL};
    // mx_echo(argv);
    system("leaks -q ush");
    return 0;
}

    
// static void test() {
//     wordexp_t p;
//     char **w;
//     size_t i;

//    int result = wordexp("echo `ls; lsf`", &p, WRDE_SHOWERR);
//     w = p.we_wordv;
//     for (i = 0; i < p.we_wordc; i++)
//         printf("%s\n", w[i]);
//     printf("code = %d\n", result);
//     wordfree(&p);
// }

static void main_cycle() {
    int result = 0;
    t_prompt *prompt = malloc(sizeof(t_prompt));
    extern char **environ;

    while (strcmp(prompt->command, "exit") && result != -1) {
        mx_get_input(prompt, &result);
        printf("\r\n");
        mx_handle_command(prompt->command, &result);
    }
    mx_d_del_list(&prompt->history_head);
    free(prompt);
    
}

static void deinit() {
    mx_disable_canon();
    // TODO
    t_map **map = mx_get_lenv();
    mx_del_map(map);
    //
}

static void init() {
    // TODO
    mx_init_var_lists();
    t_map **map = mx_get_lenv();
    char path[PATH_MAX];
    *map = mx_create_map(40);

    getcwd(path, sizeof(path));
    mx_put_map(map, strdup("OLDPWD"), strdup(getenv("OLDPWD"))); //NULL if first pwd
    mx_put_map(map, strdup("PWD"), strdup(getenv("PWD")));
    mx_put_map(map, strdup("?"), mx_itoa(0));
    mx_put_map(map, strdup("#"), mx_itoa(0));
    mx_put_map(map, strdup("0"), strdup(MX_SHELL_NAME));
    mx_put_map(map, strdup("_"), strdup(path));
    mx_put_map(map, strdup("$"), mx_itoa(getpid()));
    mx_put_map(map, strdup("*"), strdup(""));
    mx_put_map(map, strdup("@"), strdup(""));
    // sigset_t mask;
    // sigfillset(&mask);
    // sigprocmask(SIG_SETMASK, &mask, NULL);
    //
    // setenv("MX_PROMPT", "u$h> ", 0);
    // mx_var_list_insert(SHELL, "MX_PROMPT=u$h> ");
    // mx_var_list_insert(EXP, "MX_PROMPT=u$h> ");
    char *args[3] = {"MX_PROMPT=ush> ", NULL};
    mx_export(args, 1);
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}
