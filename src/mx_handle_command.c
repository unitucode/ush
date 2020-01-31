#include "ush.h"

void mx_handle_command(char *command, int *code) {
    char **commands = NULL;

    if (!strlen(command))
        return;
    if ((*code = mx_preinterpretate(command)))
        return;
    commands = mx_split_commands(command);
    mx_del_strarr(&commands);
}
