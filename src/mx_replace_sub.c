#include "ush.h"

bool mx_get_sub(char *arg, char *sub, bool is_quotes, int *code) {
    char **arguments = NULL;
    char *output = NULL;
    char **commands = NULL;

    if (mx_remove_subchar(sub)) {
        commands = mx_parse_command(sub, code);
    }
    if (*code || !commands) 
        return false;
    for (unsigned int i = 0; commands[i]; i++) {
        commands[i] = mx_replace_escape(commands[i], "\\\\",  '\\', true);
        commands[i] = mx_replace_escape(commands[i], "\\`", MX_GRAVE_ACCENT, true);
        if (!(arguments = mx_interpretate(commands[i], code))) {
            mx_del_strarr(&commands);
            mx_strdel(&sub);
            continue;
        }
        printf("sub---\n");
        for (unsigned int i = 0; arguments[i]; i++) {
            printf("arg = %s\n", arguments[i]);
        }
        printf("sub---\n");
        if (is_quotes)
            output = strdup(".+."); // todo command;
        else
            output = strdup(".-.");
        strcat(arg, output);
        mx_strdel(&output);
        mx_del_strarr(&arguments);
    }
    mx_strdel(&sub);
    mx_del_strarr(&commands);
    return true;
}
