#include "ush.h"

void mx_handle_command(char *command, int *code) {
    char **commands = mx_parse_command(command, code);
    char **arguments = NULL;

    if (*code || !commands)
        return;
    for (unsigned int i = 0; commands[i]; i++) {
        if (!(arguments = mx_interpretate(commands[i], code))) {
            continue;
        }
        // printf("cmd---\n");
        // for (int j = 0; arguments[j]; j++) {
        //     printf("arg = (%s)\n", arguments[j]);
        // }
        // printf("cmd---\n");
        mx_exec_command(arguments, 1);
        mx_del_strarr(&arguments);
    }
    mx_del_strarr(&commands);
}
