#include "ush.h"

t_list **mx_get_list_procs() {
    static t_list *list = NULL;

    return &list;
}
