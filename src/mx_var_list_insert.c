#include "ush.h"

static void push_front(t_list **node, t_list ***list) {
    (*node)->next = (**list);
    (**list) = *node;
}

static void push_mid(t_list **list, t_list **node) {
    t_list *current = *list;
    t_list *prev = NULL;
    t_list *tmp = NULL;

    while (current)
        if (strcmp(current->data, (*node)->data) < 0) {
            prev = current;
            current = current->next;
        } // IF DUPLICATE!!!
        else
            break;
    if (current == NULL)
        prev->next = *node;
    else {
        tmp = current;
        prev->next = *node;
        prev->next->next = tmp;
    }
}

void mx_var_list_insert(t_var_list key, char *arg) {
    t_list **list = mx_get_var_list(key);
    t_list *node = mx_create_node(arg);

    // t_list *current = *list;
    // t_list *prev = NULL;
    // t_list *tmp = NULL;

    if (strcmp((*list)->data, arg) > 0) { 
        (push_front(&node, &list));
        return;
    }
    push_mid(list, &node);
    // while (current)
    //     if (strcmp(current->data, arg) < 0) {
    //         prev = current;
    //         current = current->next;
    //     }
    //     else
    //         break;
    // if (current == NULL)
    //     prev->next = node;
    // else {
    //     tmp = current;
    //     prev->next = node;
    //     prev->next->next = tmp;
    // }
}
