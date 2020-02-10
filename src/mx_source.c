#include "ush.h"

char **mx_source(char *str) {
    char *file = mx_file_to_str(str);

    if (file == NULL) {
        fprintf(stderr, "%s : file error\n", str);
        return NULL;
    }
    return mx_strsplit(file, '\n');
}
