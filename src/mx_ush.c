#include "ush.h"
// #include <paths.h>

// static void test();
static void main_cycle();
static void init();
static void deinit();

int main() {
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


// static void test() { // create a new process;
//     t_process *process = mx_create_process(1);
//     char *argv[20] = {"ls", "-R", "/", NULL};
//     extern char **environ;
//     mx_exec(process, "/bin/ls", argv, environ);
//     sleep(3);
//     printf("kill\n");
//     kill(process->pid, SIGCONT);
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
    *map = mx_create_map(40);
    mx_put_map(map, strdup("OLDPWD"), strdup(getenv("OLDPWD"))); //NULL if first pwd
    mx_put_map(map, strdup("PWD"), strdup(getenv("PWD")));
    mx_put_map(map, strdup("$?"), mx_itoa(0));
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    //
    setenv("MX_PROMPT", "u$h> ", 0);
    tcgetattr(STDIN_FILENO, mx_get_tty());
    setvbuf(stdout, NULL, _IONBF, 0);
    mx_enable_canon();
}
