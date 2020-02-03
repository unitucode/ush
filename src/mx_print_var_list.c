#include "ush.h"

void mx_print_var_list(char *key) {
    t_list **var_list = mx_get_var_list(key);
    t_list *current = *var_list;

    while (current) {
        puts(current->data);
        if (current->next)
            current = current->next;
        else
            current = NULL;
    }
}
