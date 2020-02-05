#include "ush.h"

t_list **mx_get_var_list(t_var_list key) {
    static t_list *exp_list = NULL;
    static t_list *shell_list = NULL;

    if (key == EXP)
        return &exp_list;
    else if (key == SHELL)
        return &shell_list;
    return NULL;
}
