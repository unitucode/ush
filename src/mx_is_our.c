#include "ush.h"

bool mx_is_our_command(char *command) {
    if (strcmp(command, "pwd") == 0
        || strcmp(command, "cd") == 0
        || strcmp(command, "echo") == 0
        || strcmp(command, "which") == 0) {
        return 1;
    }
    return 0;
}

bool mx_is_our_builtin(char *command) {
    if (strcmp(command, "export") == 0
        || strcmp(command, "unset") == 0) {
        return 1;
    }
    return 0;
}
