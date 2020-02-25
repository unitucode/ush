#include "ush.h"

static void get_names(char *var1, char **name1, char *var2, char **name2) {
    mx_get_name(var1, name1);
    mx_get_name(var2, name2);
    if (!strcmp(*name2, "OLDPWD")) {
        t_map **map = mx_get_lenv();

        mx_put_map(map, "OLDPWD", mx_get_var_info(var2, 1));
    }
}

static void change_var_value(t_list **list, t_list *node,
                             char **name1, char **name2) {
    mx_var_list_replace_var(list, node);
    mx_delete_names(name1, name2, node);
}

void mx_var_list_insert(t_var_list key, char *arg) {
    t_list **list = mx_get_var_list(key);
    t_list *node = mx_create_node(strdup(arg));
    char *arg_name = NULL;
    char *var_name = NULL;

    if (*list) {
        get_names((*list)->data, &var_name, arg, &arg_name);
        if (strcmp(var_name, arg_name) > 0) {
            mx_var_list_push_front(&node, &list, &arg_name, &var_name);
            return;
        }
        else if (!strcmp(var_name, arg_name)) {
            change_var_value(list, node, &var_name, &arg_name);
            return;
        }
        mx_var_list_push_mid(list, &node, arg_name, &var_name);
        mx_delete_names(&var_name, &arg_name, NULL);
    }
    else
        *list = node;
}
