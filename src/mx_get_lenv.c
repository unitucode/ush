#include "ush.h"

t_map **mx_get_lenv() {
    static t_map *lenv = NULL;

    return &lenv;
}
