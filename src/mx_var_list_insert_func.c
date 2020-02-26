#include "ush.h"

void mx_var_list_push_front(t_list **node, t_list ***list,
                            char **name1, char **name2) {
    (*node)->next = (**list);
    (**list) = *node;
    mx_delete_names(name1, name2, NULL);
}

void mx_var_list_replace_var(t_list **list, t_list *node) {
    char *del = (char *)(*list)->data;

    mx_strdel(&del);
    (*list)->data = strdup(node->data);
    del = (char *)node->data;
    mx_strdel(&del);
}

static void shift_nods(t_list **current, t_list **prev, t_list **node) {
    t_list *tmp = NULL;

    if ((*current) == NULL)
        (*prev)->next = *node;
    else {
        tmp = *current;
        (*prev)->next = *node;
        (*prev)->next->next = tmp;
    }
}

void mx_var_list_push_mid(t_list **list, t_list **node,
                          char *arg_name, char **var_name) {
    t_list *current = *list;
    t_list *prev = NULL;

    while (current)
        if (strcmp(*var_name, arg_name) < 0) {
            prev = current;
            current = current->next;
            if (current)
                mx_get_name(current->data, var_name);
        }
        else if (strcmp(*var_name, arg_name) == 0) {
            mx_var_list_replace_var(&current, (*node));
            free(*node);
            return;
        }
        else
            break;
    shift_nods(&current, &prev, node);
}
