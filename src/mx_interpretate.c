#include "ush.h"

// static t_list *split_arguments(char *command);
// static char **replace_all(t_list *arguments);
// static void parse_arguments(t_list *arguments);
// static bool is_argument(char *command, unsigned int index);

char **mx_interpretate(char *command, int *code) {
    // t_list *tmp_arguments = split_arguments(command);
    // t_list *subs_arguments = mx_handle_substitution(tmp_arguments);
    // char **arguments = replace_all(subs_arguments);
    t_list *arguments = NULL;
    if (!(command = mx_replace_env(command, code))) {
        fprintf(stderr, "%s: bad substitution\n", MX_SHELL_NAME);
        return NULL; // arg for one command;
    }
    command = mx_replace_tilde(command);
    // if (!(command = mx_replace_subsitution(command, code))) {
    //     fprintf(stderr, "%s: ", MX_SHELL_NAME);
    //     return NULL;
    // }
    arguments = mx_split_command(command);
    printf("command = (%s)\n", command);
    // mx_del_list(&tmp_arguments);
    // mx_del_list(&subs_arguments);
    // return arguments;
    int len = mx_list_size(arguments);
    char **result = malloc(sizeof(char *) * (len + 1));
    result[len] = NULL;
    for (int i = 0; i < len; i++) {
        result[i] = strdup(arguments->data);
        printf("result = %s\n", result[i]);
        arguments = arguments->next;
    }
    printf("exit\n");
    return NULL;
}

// static void parse(char *command, int *code) {
//     char *result = mx_strnew(ARG_MAX);
//     unsigned int len = strlen(command);

//     strcpy(result, command);
//     result = mx_replace_env(result);
// }

// static void parse_arguments(t_list *arguments) {
//     t_list *tmp = arguments;

//     while (tmp) {
//         if (!mx_issubstitution(tmp->data)) {
//             tmp->data = mx_replace_special(tmp->data);
//         }
//         tmp = tmp->next;
//     }
// }

// static char **replace_all(t_list *arguments) {
//     int size = mx_list_size(arguments);
//     char **result = malloc(sizeof(char *) * (size + 1));
//     int i = 0;
//     char *arg = NULL;

//     result[size] = NULL;
//     while (i < size) {
//         arg = mx_strnew(ARG_MAX);
//         strcpy(arg, arguments->data);
//         result[i] = arg;
//         arguments = arguments->next;
//         i++;
//     }
//     return result;
// }

// static bool is_argument(char *command, unsigned int i) {
//     if ((isspace(command[i])
//         && !isspace(command[i + 1])
//         && !mx_isescape_char(command, i))
//         || !command[i + 1]) {
//         return true;
//     }
//     return false;
// }

// static t_list *split_arguments(char *command) {
//     t_list *arguments = NULL;
//     unsigned int len = 0;
//     char *tmp = mx_strtrim(command);
//     char *tmp_arg = NULL;

//     for (unsigned int i = 0; i < strlen(tmp); i++) {
//         mx_skip_expansion(tmp, &i);
//         mx_skip_quotes(tmp, &i, '\"');
//         mx_skip_quotes(tmp, &i, '\'');
//         mx_skip_quotes(tmp, &i, '`');
//         if (is_argument(tmp, i)) {
//             if (!tmp[i + 1])
//                 i++;
//             tmp_arg = strndup(tmp + len, i - len);
//             mx_push_back(&arguments, mx_strtrim(tmp_arg));
//             mx_strdel(&tmp_arg);
//             len = i;
//         }
//     }
//     mx_strdel(&tmp);
//     parse_arguments(arguments);
//     return arguments;
// }
