#include "ush.h"

t_list *mx_handle_substitution(t_list *arguments) {
    t_list *result = NULL;

    while (arguments) {
        mx_push_back(&result, strdup(arguments->data));
        arguments = arguments->next;
    }
    return result;
}
