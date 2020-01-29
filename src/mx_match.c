#include "ush.h"

bool mx_match(char *src, char *regex) {
    regex_t reg;
    int result;

    regcomp(&reg, regex, REG_EXTENDED);
    result = regexec(&reg, src, 0, NULL, 0);
    regfree(&reg);
    return result == 0;
}
