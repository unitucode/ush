#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <limits.h>
#include <termios.h>
#include <fcntl.h>
#include <ctype.h>
#include "inc/libmx.h"

#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h"

int mx_get_input(char *buf);
