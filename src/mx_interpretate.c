#include "ush.h"

char **mx_interpretate(char *command) {
    char **commands = NULL;

    if (!mx_check_quotes(command)) {
        return NULL;
    }
    // commands = mx_split_semicolon(command);
    return commands;
}
