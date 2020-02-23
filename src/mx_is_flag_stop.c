#include <stdbool.h>

bool mx_is_flag_stop(char *flag) {
    if ((flag[1] == '-' && flag[2] == '\0') 
        || flag[1] == '\0') {
        return true;
    }
    return false;
}
