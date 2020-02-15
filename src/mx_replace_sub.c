#include "ush.h"

bool mx_get_sub(char *arg, char *sub, bool is_quotes, int *code) {
    char **arguments = NULL;
    char *output = NULL;

    mx_remove_subchar(sub);
    sub = mx_replace_escape(sub, "\\`", MX_GRAVE_ACCENT, true);
    sub = mx_replace_escape(sub, "\\\\",  '\\', true);
    if (!(arguments = mx_interpretate(sub, code))) {
        mx_strdel(&sub);
        return false;
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
    mx_strdel(&sub);
    mx_strdel(&output);
    mx_del_strarr(&arguments);
    return true;
}
