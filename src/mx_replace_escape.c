#include "ush.h"

char *mx_replace_escape(char *arg, char *escape, char new, bool in_q) {
    bool d_q = false;
    char *result = mx_strnew(ARG_MAX);
    unsigned int index = 0;

    for (unsigned int i = 0; i < strlen(arg); i++) {
        if (arg[i] == MX_D_QUOTES && !mx_isescape_char(arg, i))
            d_q = !d_q;
        if (arg[i] == escape[0]
            && arg[i + 1] == escape[1]
            && mx_isescape_char(arg, i + 1)
            && (d_q || in_q)) {
            i++;
            arg[i] = new;
        }
        result[index++] = arg[i];
    }
    mx_strdel(&arg);
    return result;
}
