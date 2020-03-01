#include "ush.h"

bool mx_is_builtin(char *command) {
    if (!strcmp(command, "pwd")
        || !strcmp(command, "cd")
        || !strcmp(command, "fg")
        || !strcmp(command, "fg")
        || !strcmp(command, "set")
        || !strcmp(command, "env")
        || !strcmp(command, "true")
        || !strcmp(command, "echo")
        || !strcmp(command, "jobs")
        || !strcmp(command, "exit")
        || !strcmp(command, "unset")
        || !strcmp(command, "color")
        || !strcmp(command, "false")
        || !strcmp(command, "which")
        || !strcmp(command, "chdir")
        || !strcmp(command, "export")) {
        return 1;
    }
    return 0;
}
