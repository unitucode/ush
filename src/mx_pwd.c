#include "ush.h"

int mx_pwd(char *flags) {
    if (mx_strcmp(flags, "") == 0)
        printf("%s", getenv("PWD"));
    else if (mx_strcmp(flags, "-P")) {
        
    }
    else if (mx_strcmp(flags, "-L")) {
        
    }
    else {
        fprintf(stderr, "pwd: bad option: %s\n", flags);
    }
}
