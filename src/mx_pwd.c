#include "ush.h"

static bool pars_flag(char **flags, bool *mode);
static void cross_dir();

bool mx_pwd(char *flags) {
    bool mode = 0;
    bool exit_status = 0;

    while (*flags != '\0') {
        if (*flags != ' ') {
            if (*flags == '-')
                exit_status = pars_flag(&flags, &mode);
            else
                fprintf(stderr, "%s", "pwd: too many arguments");
                return 1;
        }
        flags++;
    }
    if (mode == 1)
        cross_dir();
    else
        printf("%s", getenv("PWD"));
    return exit_status;
}

static void cross_dir() {
    printf("Flag -P");
}

static bool pars_flag(char **flags, bool *mode) {
    (*flags)++;
    while (**flags != ' ' && **flags != '\0') {
        if (**flags == 'P')
            *mode = 1;
        else if (**flags != 'L') {
            fprintf(stderr, "%s%c", "pwd: bad option: -", **flags);
            return 1;
        }
        (*flags)++;
    }
    return 0;
}
