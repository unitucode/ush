#include "ush.h"

void mx_delete_names(char **name1, char **name2, t_list *node) {
    mx_strdel(name1);
    mx_strdel(name2);
    free(node);
}
