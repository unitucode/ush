#include "ush.h"

t_list **mx_get_var_list(t_var_list key) {
    static t_list *exp_list = NULL;
    static t_list *shell_list = NULL;

    if (key == exp)
        return &exp_list;
    return &shell_list;
}
