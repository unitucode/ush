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
#include <sys/ioctl.h>
#include "inc/libmx.h"

#define MX_SHELL_NAME "ush"
#define MX_SHELL_PROMPT "u$h> "
#define MX_UP_ARROW "\x1b\x5b\x41"
#define MX_DOWN_ARROW "\x1b\x5b\x42"
#define MX_RIGHT_ARROW "\x1b\x5b\x43"
#define MX_LEFT_ARROW "\x1b\x5b\x44"
#define MX_MOVE_CURSOR_LEFT "\x1b[1C"
#define MX_MOVE_CURSOR_RIGHT "\x1b[1D"
#define MX_DELETE_KEY "\x1b\x5b\x33\x7e"
#define MX_HOME_KEY "\x1b\x5b\x48"
#define MX_END_KEY "\x1b\x5b\x46"
#define MX_NON_PRINTABLE "[\x03\x0a]"
#define MX_NEW_LINE_CHARS "^[\x03\x0a]$"
#define MX_S_QUOTE '\''
#define MX_GRAVE_ACCENT '`'
#define MX_HISTORY_SIZE 20
#define MX_EXPORT_ARG "^[A-Za-z_]+[A-Za-z0-9_]*(=.*)?$"

typedef struct s_prompt {
    unsigned int index;
    unsigned int cursor_index;
    bool end;
    t_d_list *history_head;
    t_d_list *history_back;
    t_d_list *tmp_history;
    char buff[5];
    char command[ARG_MAX + 1];
    char tmp_command[ARG_MAX + 1];
} t_prompt;


// void mx_get_input(char *buf, int *code);
void mx_get_input(t_prompt * prompt, int *code);
struct termios *mx_get_tty();
void mx_enable_canon();
void mx_disable_canon();
bool mx_match(char *src, char *regex);
void mx_print_env();
bool mx_is_flag_stop(char *flag);
void mx_backspace(unsigned int times);
void mx_handle_print_char(t_prompt *prompt);
bool mx_handle_history(t_prompt *prompt);
void mx_update_history(t_prompt *prompt);
void mx_rcmd(char *dst, char *src, size_t size, unsigned int *index);
t_map **mx_get_lenv();
char *mx_str_prompt();
void mx_handle_cursor(t_prompt *prompt);
char **mx_interpretate(char *command);
bool mx_check_quotes(char *command);
char **mx_split_commands(char *command);
void mx_print_sh_error(char *process, char *message);
int mx_preinterpretate(char *command);
void mx_handle_command(char *command, int *code);

char *mx_parse_path(char *pwd, char *newdir, t_map **map);
char *mx_clear_slashes_end(char *str);
void mx_change_dir(char *newdir, t_map **map);
void mx_cd_flags(char *flag, t_map **map, char *newdir);
void mx_change_map(t_map **map, char *newdir);

int mx_unset(char **args);
int mx_export(char **args);
int mx_pwd(char **flags);
int mx_cd(char **args, t_map **map);
int mx_which(char **args);
