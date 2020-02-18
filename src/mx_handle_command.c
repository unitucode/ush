#include "ush.h"

void mx_handle_command(char *command, int *code) {
    char **commands = mx_parse_command(command, code);
    char **arguments = NULL;
    t_map **map = mx_get_lenv();

    if (*code || !commands) {
        mx_put_map(map, "?", mx_itoa(*code));
        return;
    }
    for (unsigned int i = 0; commands[i]; i++) {
        if (!(arguments = mx_interpretate(commands[i], code))) {
            mx_put_map(map, "?", mx_itoa(*code));
            continue;
        }
        *code = mx_exec_command(arguments, 1);
        mx_put_map(map, "?", mx_itoa(*code));
        mx_del_strarr(&arguments);
    }
    mx_del_strarr(&commands);
}
