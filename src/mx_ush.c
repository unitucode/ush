#include "ush.h"

int main() {
    bool retval = mx_pwd("-P");

    system("leaks -q ush");
    return retval;
}
