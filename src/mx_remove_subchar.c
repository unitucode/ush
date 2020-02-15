#include "ush.h"

void mx_remove_subchar(char *substitution) {
    unsigned int len = strlen(substitution);

    if (substitution[0] == '`' && substitution[len - 1] == '`') {
        substitution[len - 1] = '\0';
        memmove(substitution, substitution + 1, len - 1);
        return;
    }
    if (substitution[0] == '$' && substitution[1] == '('
        && substitution[len - 1] == ')') {
        substitution[len - 1] = '\0';
        memmove(substitution, substitution + 2, len - 2);
        return;
    }
}
