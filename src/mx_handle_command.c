#include "ush.h"

void mx_handle_command(char *command, int *code) {
    char **commands = NULL;
    char **arguments = NULL;

    if (!strlen(command))
        return;
    if ((*code = mx_preinterpretate(command)))
        return;
    commands = mx_split_commands(command);
    for (unsigned int i = 0; commands[i]; i++) {
        arguments = mx_interpretate(commands[i]);
    }
    mx_del_strarr(&commands);
}
