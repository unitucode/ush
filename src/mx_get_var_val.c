#include "ush.h"

char *mx_get_var_val(char *key, char *var) {
    t_list **list = mx_get_var_list(key);
    t_list *current = *list;
    char *search = mx_strjoin(var, "=");
    int len = strlen(search);

    while (current)
        if (strncmp(current->data, search, len) != 0)
            current = current->next;
        else
            break;
    return strdup((char *)(current->data) + len);
}
