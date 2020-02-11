#include "ush.h"

void mx_handle_command(char *command, int *code) {
    char **commands = mx_parse_command(command, code);
    char **arguments = NULL;

    if (*code || !commands)
        return;
    for (unsigned int i = 0; commands[i]; i++) {
        if (!(arguments = mx_interpretate(commands[i], code)))
            return;
        printf("cmd---\n");
        for (unsigned int i = 0; arguments[i]; i++) {
            printf("arg = (%s)\n", arguments[i]);
        }
        printf("cmd---\n");
        mx_del_strarr(&arguments);
    }
    mx_del_strarr(&commands);
}
