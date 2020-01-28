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
#include "inc/libmx.h"

#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h"
#define MX_NEW_LINE_CHARS "[\x03\x0a]"

typedef struct s_prompt {
    unsigned int index;
    unsigned int cursor_index;
    char buff[5];
    char command[ARG_MAX + 1];
} t_prompt;

#define MX_UP_ARROW "\x1b\x5b\x41"
#define MX_DOWN_ARROW "\x1b\x5b\x42"
#define MX_RIGHT_ARROW "\x1b\x5b\x43"
#define MX_LEFT_ARROW "\x1b\x5b\x44"
#define MX_MOVE_CURSOR_RIGHT "\x1b[1C"
#define MX_MOVE_CURSOR_LEFT "\x1b[1D"

// void mx_get_input(char *buf, int *code);
void mx_get_input(t_prompt * prompt, int *code);
struct termios *mx_get_tty();
void mx_enable_canon();
void mx_disable_canon();
bool mx_match(char *src, char *regex);
void mx_backspace(unsigned int times);
void mx_handle_arrows(t_prompt *prompt);
void mx_handle_print_char(t_prompt *prompt);

int mx_unset(char *name);
void mx_export(char *str);
int mx_pwd(char **flags);
