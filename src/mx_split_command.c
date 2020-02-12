#include "ush.h"

t_list *mx_split_command(char *command) {
    t_list *result = NULL;
    unsigned int save = 0;

    for (unsigned int i = 0; i < strlen(command); i++) {
        mx_skip_quotes(command, &i, MX_D_QUOTES);
        mx_skip_quotes(command, &i, MX_S_QUOTES);
        if (!command[i + 1] || (!isspace(command[i]) && isspace(command[i + 1] && !mx_isescape_char(command, i)))) {
            mx_push_back(&result, strndup(command + save, i - save + 1));
            save = i + 1;
        }
        else if(isspace(command[i]) && !mx_isescape_char(command, i))
            save++;
    }
    return result;
}
