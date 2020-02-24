#include "ush.h"

bool mx_check_dir_exists(char *dir) {
    if (chdir(dir) < 0)
        return false;
    else
        chdir("..");
    return true;
}
