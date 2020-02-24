#include "ush.h"

bool mx_issubstitution(char *arg) {
    unsigned int len = strlen(arg);
    bool result = false;

    if (arg[0] == '`' && arg[len - 1] == '`')
        result = true;
    if (arg[0] == '$' && arg[1] == '(' && arg[len - 1] == ')')
        result = true;
    return result;
}
