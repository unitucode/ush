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
#define MX_EXPORT_ARG "^[A-Za-z_]+[A-Za-z0-9_]*=?[A-Za-z0-9_]*$"
#define MX_ENV_ARG "^[A-Za-z_]+[A-Za-z0-9_]*="
#define MX_NEW_LINE_CHARS "[\x03\x0a]"
#define MX_HISTORY_SIZE 20

typedef struct s_prompt {
    unsigned int index;
    bool ishistory;
    t_d_list *history_head;
    t_d_list *history_back;
    t_d_list *tmp_history;
    char buff[5];
    char command[ARG_MAX + 1];
    char tmp_command[ARG_MAX + 1];
} t_prompt;

#define MX_UP_ARROW "\x1b\x5b\x41"
#define MX_DOWN_ARROW "\x1b\x5b\x42"

// void mx_get_input(char *buf, int *code);
void mx_get_input(t_prompt * prompt, int *code);
struct termios *mx_get_tty();
void mx_enable_canon();
void mx_disable_canon();
bool mx_match(char *src, char *regex);
void mx_print_env();
void mx_backspace(unsigned int times);
void mx_handle_print_char(t_prompt *prompt);
bool mx_handle_history(t_prompt *prompt);
void mx_update_history(t_prompt *prompt);

int mx_unset(char *name);
int mx_export(char **args);
int mx_pwd(char **flags);
