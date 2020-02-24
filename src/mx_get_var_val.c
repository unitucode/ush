#include "ush.h"

char *mx_get_var_val(t_var_list key, char *var) {
    t_list **list = mx_get_var_list(key);
    t_list *current = *list;
    char *search = mx_strjoin(var, "=");
    int len = strlen(search);

    while (current) {
        if (strncmp(current->data, search, len) != 0)
            current = current->next;
        else
            break;
    }
    mx_strdel(&search);
    if (current == NULL)
        return NULL;
    return (char*)(current->data) + len;
}
