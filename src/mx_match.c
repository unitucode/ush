#include "ush.h"

bool mx_match(char *src, char *regex) {
    regex_t reg;
    int result;

    result = regcomp(&reg, regex, 0);
    result = regexec(&reg, src, 0, NULL, 0);
    regfree(&reg);
    return result != REG_NOMATCH;
}
