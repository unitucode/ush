#include "ush.h"

void mx_exit(char **args) {
    int code = 0;
<<<<<<< HEAD

    mx_disable_canon();
    system("leaks -q ush");
=======
    system("leaks -q ush");
    mx_deinit();
>>>>>>> f173e170b4415161bf33cd723bf2731273cfdd8e
    if (!*args) {
        exit(code);
    }
    if (mx_arr_size(args) > 1) {
        fprintf(stderr, "exit: too many arguments\n");
        exit(1);
    }
    for (unsigned int i = 0; i < strlen(args[0]); i++)
        if (!isnumber(args[0][i])) {
            fprintf(stderr, "exit: bad argument\n");
            exit(1);
        }
    code = atoi(args[0]);
    exit(code);
}
