#include "ush.h"

static bool is_number_arg(char *arg) {
    for (unsigned int i = 0; i < strlen(arg); i++) {
        if (!isnumber(arg[i])) {
            return false;
        }
    }
    return true;
}

int mx_exit(char **args) {
    int code = 0;

    if (mx_arr_size(args) > 1 && is_number_arg(args[0])) {
        fprintf(stderr, "exit: too many arguments\n");
        return 1;    
    }
    mx_deinit();
    if (!*args) {
        exit(code);
    }
    for (unsigned int i = 0; i < strlen(args[0]); i++) {
        if (!isnumber(args[0][i])) {
            fprintf(stderr, "exit: bad argument\n");
            exit(1);
        }
    }
    code = atoi(args[0]);
    exit(code);
}
