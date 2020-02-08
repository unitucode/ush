#include "ush.h"

void mx_parse_substitution(t_list **result, char *substitution) {
    char **commands = NULL;
    char *tmp = NULL;
    char **arguments = NULL;
    bool sub_type;
    int *code = 0;

    sub_type = mx_remove_subchar(substitution);
    if (!strlen(substitution))
        return;
    tmp = mx_strtrim(substitution);
    if (sub_type)
        tmp = mx_replace_special(tmp);
    commands = mx_split_commands(tmp);
    for (unsigned int i = 0; commands[i]; i++) {
        arguments = mx_interpretate(commands[i], code);
        printf("subs---\n");
        for (unsigned int i = 0; arguments[i]; i++) {
            printf("arg = (%s)\n", arguments[i]);
        }
        printf("subs---\n");
        mx_push_back(result, strdup("done!")); // push output
        mx_del_strarr(&arguments);
    }
    mx_strdel(&substitution);
    mx_strdel(&tmp);
    mx_del_strarr(&commands);
}
