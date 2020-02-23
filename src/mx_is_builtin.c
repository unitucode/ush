#include "ush.h"

bool mx_is_builtin(char *command) {
    if (!strcmp(command, "pwd")
        || !strcmp(command, "cd")
        || !strcmp(command, "fg")
        || !strcmp(command, "env")
        || !strcmp(command, "true")
        || !strcmp(command, "echo")
        || !strcmp(command, "exit")
        || !strcmp(command, "unset")
        || !strcmp(command, "color")
        || !strcmp(command, "false")
        || !strcmp(command, "export")
        || !strcmp(command, "which")
        || !strcmp(command, "echo")
        || !strcmp(command, "jobs")
        || !strcmp(command, "fg")) {
        return 1;
    }
    return 0;
}
