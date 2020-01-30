#include "ush.h"

void mx_rcmd(char *dst, char *src, size_t size, unsigned int *index) {
    memset(dst, '\0', size);
    strcpy(dst, src);
    *index = strlen(src);
}
