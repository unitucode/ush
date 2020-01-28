#include "ush.h"

static void print_env();
// static char *get_var_name(char *str);

int mx_export(char **args) {
    if (args[0] == NULL)
        print_env();
    else {
        for (int i = 0; args[i]; i++) {
            if (mx_match(args[i], MX_EXPORT_ARG))
                printf("%s\n", args[i]);
            else
                printf("ERROR: %s\n", args[i]);
        }
    }
    return 0;
}

static void print_env() {
    extern char **environ;
    int len = 0;

    for (int i = 0; environ[i]; i++)
        len++;
    mx_bubble_sort(environ, len);
    mx_print_strarr(environ, "\n");
}

// static char *get_var_name(char *str) {
//     char *name = mx_strndup(str, mx_get_char_index(str, '='));

//     return name;
// }
// static int test()
// {
//     reti = regcomp(&regex, MX_EXPORT_ARG, 0);
//     if (reti)
//     {
//         fprintf(stderr, "Could not compile regex\n");
//         exit(1);
//     }

//     reti = regexec(&regex, "A=a", 0, NULL, 0);
//     if (!reti)
//     {
//         puts("Match");
//     }
//     else if (reti == REG_NOMATCH)
//     {
//         puts("No match");
//     }
//     else
//     {
//         regerror(reti, &regex, msgbuf, sizeof(msgbuf));
//         fprintf(stderr, "Regex match failed: %s\n", msgbuf);
//         exit(1);
//     }
//     return 0;
// }
