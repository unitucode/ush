#include "ush.h"

static void run(char **arguments);

void mx_handle_command(char *command, int *code) {
    char **commands = NULL;
    char **arguments = NULL;

    if (!strlen(command))
        return;
    if ((*code = mx_preinterpretate(command)))
        return;
    commands = mx_split_commands(command);
    if (!mx_check_semicolons(commands, code))
        return;
    for (unsigned int i = 0; commands[i]; i++) {
        arguments = mx_interpretate(commands[i]); // arg for one command;
        run(arguments); //TODO
    }
    mx_del_strarr(&commands);
}

static void run(char **arguments) {
    if (!strcmp(*arguments, "echo")) {
        mx_echo(arguments + 1);
    }
    if (!strcmp(*arguments, "pwd")) {
        mx_pwd(arguments + 1);
    }
}
