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
#include <spawn.h>
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
#define MX_D_QUOTES '\"'
#define MX_S_QUOTES '\''
#define MX_GRAVE_ACCENT '`'
#define MX_ESCAPE_CHARS "\\\"\'ntva$` "
#define MX_HISTORY_SIZE 20
#define MX_EXPORT_ARG "^[A-Za-z_]+[A-Za-z0-9_]*(=.*)?$"
#define MX_UNSET_ARG "^([0-9]+|[A-Za-z_]+[0-9A-Za-z_]*)$"

#define MX_ISREG(m) (((m)&S_IFMT) == S_IFREG)

typedef enum e_var_list {
    SHELL,
    EXP
} t_var_list;

typedef struct s_process {
    posix_spawn_file_actions_t actions;
    posix_spawnattr_t attrs;
    pid_t pid;
    sigset_t signals;
} t_process;

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
char **mx_interpretate(char *command, int *code);
bool mx_check_quotes(char *command);
char **mx_split_commands(char *command);
void mx_print_sh_error(char *process, char *message);
int mx_preinterpretate(char *command);
void mx_handle_command(char *command, int *code);
t_list **mx_get_var_list(t_var_list key);
void mx_init_var_lists();
void mx_print_var_list(t_var_list key);
void mx_var_list_insert(t_var_list key, char *arg);
char *mx_get_var_info(char *arg, bool info_type);
char *mx_get_var_val(t_var_list key, char *var);
bool mx_check_escape(char *command);
bool mx_isescape_char(char *command, int i);
char *mx_replace_special(char *argument);
char *mx_replace_escape(char *arg, char *escape, char new, bool in_q);
char *mx_replace_env(char *arg);
void mx_get_name(char *var, char **name);
void mx_delete_names(char **name1, char **name2, t_list *node);
bool mx_check_semicolons(char **commands, int *code);
bool mx_issubstitution(char *arg);
int mx_exec(t_process *process, char *filename, char **argv, char **env);
t_process *mx_create_process(int fd);
t_list *mx_handle_substitution(t_list *arguments);
void mx_parse_substitution(t_list **result, char *substitution);
bool mx_remove_subchar(char *substitution);
void mx_skip_expansion(char *command, unsigned int *i);
void mx_skip_quotes(char *command, unsigned int *i, char c);
char **mx_parse_command(char *command, int *code);
bool mx_check_substitutions(char *command);
void mx_var_list_delete(t_var_list key, char *del_name);

char *mx_parse_path(char *pwd, char *newdir, t_map **map);
char **mx_make_null_index(char **split, int index);
void mx_change_dir(char *newdir, t_map **map);
void mx_cd_flags(char *flag, t_map **map, char *newdir);
void mx_change_map(t_map **map, char *newdir);

int mx_true();
int mx_false();
int mx_echo(char **args);
int mx_unset(char **args);
int mx_export(char **args);
int mx_pwd(char **flags);
int mx_cd(char **args);
int mx_which(char **args);
char **mx_source(char *str);
