#include "ush.h"

static void pop_curr_node(t_list **list, t_list **prev, t_list **current) {
    if (*prev == NULL) {
        *prev = (*current)->next;
        *list = *prev;
    }
    else
        (*prev)->next = (*current)->next;
    free((*current)->data);
    free(*current);
    *current = NULL;
}

void mx_var_list_delete(t_var_list key, char *del_name) {
    t_list **list = mx_get_var_list(key);
    t_list *current = *list;
    t_list *prev = NULL;
    char *curr_name = NULL;

    while (current) {
        mx_get_name(current->data, &curr_name);
        if (strcmp(del_name, curr_name) == 0) {
            pop_curr_node(list, &prev, &current);
            break;
        }
        prev = current;
        current = current->next;
        if (current)
            mx_get_name(current->data, &curr_name);
    }
    mx_strdel(&curr_name);
}
