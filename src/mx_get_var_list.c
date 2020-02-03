#include "ush.h"

t_list **mx_get_var_list(char *key) {
    static t_list *exp_list = NULL;
    static t_list *shell_list = NULL;

    if (strcmp(key, "exp") == 0)
        return &exp_list;
    return &shell_list;
}
