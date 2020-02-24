#include "ush.h"

bool mx_check_brackets(char *c) {
    unsigned int len = strlen(c);
    int stack[len];
    int top = -1;

    for (unsigned int i = 0; i < len; i++) {
        mx_skip_quotes(c, &i, MX_GRAVE_ACCENT);
        if ((c[i] == '(' && !mx_isescape_char(c, i))
            || (c[i] == '{' && !mx_isescape_char(c, i))
            || (c[i] == ')' && !mx_isescape_char(c, i))
            || (c[i] == '}' && !mx_isescape_char(c, i))) {
            top++;
            stack[top] = c[i];
        }
        if ((stack[top] == ')' && (top - 1 >= 0 && stack[top - 1] == '('))
            || (stack[top] == '}' && (top - 1 >= 0
            && stack[top - 1] == '{'))) {
            top = top - 2;
        }
    }
    return top == -1;
}
