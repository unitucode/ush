#include "ush.h"

t_list *mx_handle_substitution(t_list *arguments) {
    t_list *result = NULL;

    while (arguments) {
        if (mx_issubstitution(arguments->data)) {
            mx_parse_substitution(&result, strdup(arguments->data));
        }
        else {
            mx_push_back(&result, strdup(arguments->data));
        }
        arguments = arguments->next;
    }
    return result;
}
