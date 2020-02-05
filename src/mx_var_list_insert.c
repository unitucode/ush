#include "ush.h"

static void push_front(t_list **node, t_list ***list,
                       char **name1, char **name2) {
    (*node)->next = (**list);
    (**list) = *node;
    mx_delete_names(name1, name2, NULL);
}

static void replace_var(t_list **list, t_list *node) {
    char *del = (char *)(*list)->data;

    mx_strdel(&del);
    (*list)->data = strdup(node->data);
    del = (char *)node->data;
    mx_strdel(&del);
}

static void push_mid(t_list **list, t_list **node,
                     char *arg_name, char **var_name) {
    t_list *current = *list;
    t_list *prev = NULL;
    t_list *tmp = NULL;

    while (current)
        if (strcmp(*var_name, arg_name) < 0) {
            prev = current;
            current = current->next;
            if (current)
                mx_get_name(current->data, var_name);
        }
        else if (strcmp(*var_name, arg_name) == 0) {
            replace_var(&current, (*node));
            free(*node);
            return ;
        }
        else
            break ;
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
    t_list *node = mx_create_node(strdup(arg));
    char *arg_name = NULL;
    char *var_name = NULL;

    mx_get_name((*list)->data, &var_name);
    mx_get_name(arg, &arg_name);
    if (strcmp(var_name, arg_name) > 0) {
        push_front(&node, &list, &arg_name, &var_name);
        return ;
    }
    else if (strcmp(var_name, arg_name) == 0) {
        replace_var(list, node);
        mx_delete_names(&var_name, &arg_name, node);
        return ;
    }
    push_mid(list, &node, arg_name, &var_name);
    mx_delete_names(&var_name, &arg_name, NULL);
}
