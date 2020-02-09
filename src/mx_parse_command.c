#include "ush.h"
    
char **mx_parse_command(char *command, int *code) {
    char **commands = NULL;

    if (!strlen(command))
        return NULL;
    if ((*code = mx_preinterpretate(command)))
        return NULL;
    commands = mx_split_commands(command);
    if (!mx_check_semicolons(commands, code)) {
        mx_del_strarr(&commands);
        return NULL;
    }
    return commands;
}
