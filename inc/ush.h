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
#include <regex.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "inc/libmx.h"

#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h"
#define MX_NON_PRINTABLE "[\x03\x0a]"

void mx_get_input(char *buf, int *code);
struct termios *mx_get_tty();
void mx_enable_canon();
void mx_disable_canon();
bool mx_match(char *src, char *regex);

int mx_unset(char *name);
void mx_export(char *str);
int mx_pwd(char **flags);
