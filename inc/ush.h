#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <termios.h>
#include <fcntl.h>
#include <ctype.h>
#include <regex.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <spawn.h>
#include <libgen.h>
#include <wordexp.h>
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
#define MX_FORBIDDEN_CHARS "|&><"
#define MX_HISTORY_SIZE 200
#define MX_EXPORT_ARG "^[A-Za-z_]+[A-Za-z0-9_]*(=.*)?$"
#define MX_ENV_NAME "^[A-Za-z_]+[A-Za-z0-9_]*$"
#define MX_UNSET_ARG "^([0-9]+|[A-Za-z_]+[0-9A-Za-z_]*)$"
#define MX_ENV_FLAG_I "^-(i*|i+.*|-.+)$"
#define MX_ENV_VAR "^.+=.*$"
#define MX_SPEC_ENV "$?#*@_0"

#define MX_W_INT(m) (*(int*) & (m))
#define MX_WSTOPSIG(m) (MX_W_INT(m) >> 8)
#define MX_WSTATUS(m) (MX_W_INT(m) & 0177)
#define MX_WIFSTOPPED(m) (MX_WSTATUS(m) == _WSTOPPED && MX_WSTOPSIG(m) != 0x13)
#define MX_ISREG(m) (((m) & S_IFMT) == S_IFREG)
#define MX_WAIT_TO_INT(m) (*(int *) & (m))
#define MX_WEXITSTATUS(x) ((MX_WAIT_TO_INT(x) >> 8) & 0x000000ff)

typedef enum e_var_list
{
    SHELL,
    EXP
}            t_var_list;

typedef struct s_process
{
    int fd;
    int pos;
    char *cmd;
    int status;
    posix_spawn_file_actions_t actions;
    posix_spawnattr_t attrs;
    pid_t pid;
    pid_t gpid;
    sigset_t signals;
}              t_process;

typedef struct s_prompt
{
    unsigned int index;
    unsigned int cursor_index;
    bool end;
    t_d_list *history_head;
    t_d_list *history_back;
    t_d_list *tmp_history;
    char buff[5];
    char command[ARG_MAX + 1];
    char tmp_command[ARG_MAX + 1];
}              t_prompt;

void mx_get_input(t_prompt * prompt, int fd, int *code);
struct termios *mx_get_tty(void);
void mx_enable_canon(void);
void mx_disable_canon(void);
bool mx_match(char *src, char *regex);
void mx_print_env(int fd);
bool mx_is_flag_stop(char *flag);
void mx_backspace(unsigned int times, int fd);
void mx_handle_print_char(t_prompt *prompt);
bool mx_handle_history(t_prompt *prompt);
void mx_update_history(t_prompt *prompt);
void mx_rcmd(char *dst, char *src, size_t size, unsigned int *index);
t_map **mx_get_lenv(void);
char *mx_str_prompt(void);
void mx_handle_cursor(t_prompt *prompt);
char **mx_interpretate(char *command, int *code);
bool mx_check_quotes(char *command);
char **mx_split_commands(char *command);
void mx_print_sh_error(char *process, char *message);
int mx_preinterpretate(char *command);
void mx_handle_command(char *command, int *code);
t_list **mx_get_var_list(t_var_list key);
void mx_print_var_list(t_var_list key, int fd);
void mx_var_list_insert(t_var_list key, char *arg);
void mx_var_list_push_front(t_list **node, t_list ***list,
                       char **name1, char **name2);
void mx_var_list_replace_var(t_list **list, t_list *node);
void mx_var_list_push_mid(t_list **list, t_list **node,
                     char *arg_name, char **var_name);
char *mx_get_var_info(char *arg, bool info_type);
char *mx_get_var_val(t_var_list key, char *var);
bool mx_check_escape(char *command);
bool mx_isescape_char(char *command, int i);
char *mx_replace_special(char *argument);
char *mx_replace_escape(char *arg, char *escape, char new, bool in_q);
char *mx_replace_env(char *arg, int *code);
void mx_get_name(char *var, char **name);
void mx_delete_names(char **name1, char **name2, t_list *node);
bool mx_check_semicolons(char **commands, int *code);
bool mx_check_brackets(char *command);
bool mx_issubstitution(char *arg);
int mx_exec(t_process *process, char *filename, char **argv, char **env);
int mx_env_exec(t_process *process, char *filename, char **argv, char **env);
char **mx_exec_copy_argv(char **argv);
t_process *mx_create_process(int fd);
void mx_del_process(t_process **process);
t_list *mx_handle_substitution(t_list *arguments);
bool mx_remove_subchar(char *substitution);
void mx_skip_expansion(char *command, unsigned int *i);
void mx_skip_quotes(char *command, unsigned int *i, char c);
char **mx_parse_command(char *command, int *code);
bool mx_check_substitutions(char *command);
void mx_var_list_delete(t_var_list key, char *del_name);
int mx_exec_command(char **argv, int fd);
char *mx_replace_tilde(char *arg);
t_list *mx_split_command(char *command);
bool mx_find_command(char *path, char *command, char **filename);
char *mx_replace_substitution(char *arg, int *code);
bool mx_get_sub(char *arg, char *sub, int *code);
t_process *mx_get_process_by_id(int id);
bool mx_check_chars(char *command);
void mx_del_node_list(t_list **list, t_process **process);
void mx_enable_signals(t_process *process);
void mx_disable_signals(t_process *process);
void mx_continue_process(t_process *process, t_list **all_processes, int fd);
void mx_skip_exps_quots(char *arg, unsigned int *index, bool *is_quotes);
bool mx_replace_env_var(char *result, char *env, unsigned int *index,
                        unsigned int len);
void mx_inc_val_var(unsigned int *len, unsigned int add, char *var);
void mx_skip_quotes_if(bool *is_quotes, char *arg, unsigned int *i);
char *mx_get_invalid_sub(char **arg, char **result, char **sub);
void mx_kill_process(void);
void mx_replace_sub_escapes(char **commands);
void mx_exec_fork(char **arguments, int fd);
bool check_stdin(int *exit_code);
t_list *mx_get_last_process(t_list *processes);
char *mx_get_output_fd(int fd);
char *mx_check_user_file(char *tmp_name);
bool mx_check_user(char *user_name);
void mx_kill_process();
void mx_print_color(int color);
void mx_init(void);
void mx_init_var_lists(void);
void mx_init_map_vars(void);
void mx_init_signals(void);
void mx_deinit(void);

char *mx_parse_path(char *pwd, char *newdir, t_map **map);
char **mx_make_null_index(char **split, int index);
bool mx_is_builtin(char *command);
void mx_increment_shlvl(void);
void mx_change_dir(char *newdir, t_map **map, int fd);
void mx_cd_flags(char *flag, t_map **map, char *newdir);
void mx_change_map(t_map **map, char *newdir);
void mx_put_pwd(char *pwd, char *oldpwd);
char **mx_env_copy(void);
int mx_print_env_error(char option, char *err_arg, int error);
void mx_putenv(char *var);
void mx_clearenv(void);
void mx_env_fill(char **src);
void mx_env_parse_vars(char **argv, char **path, int *idx);
int mx_env_parse_flags(char **argv, char **path, int *idx);

void mx_check_s_slash(char *newdir, t_map **map);
void mx_oldpwd(char *newdir, t_map **map, int fd);
void mx_home(t_map **map);
void mx_flag_p_slash(char *newdir, t_map **map);
void mx_flag_p_full_path(t_map **map, char *newdir);
char *mx_clear_slash_end(char *str);

t_list **mx_get_list_procs(void);
void mx_pop_process(int id);
int mx_get_process_id_by_pid(pid_t pid);
pid_t mx_get_process_pid_by_id(int id);

int mx_chdir(char **split, int fd);
int mx_color(char **args);
int mx_jobs(char **args, int fd);
int mx_exit(char **args);
int mx_true(void);
int mx_false(void);
int mx_echo(char **args, int fd);
int mx_unset(char **args);
int mx_export(char **args, int fd);
int mx_pwd(char **flags, int fd);
int mx_cd(char **args, int fd);
int mx_which(char **args, int fd);
int mx_env(char **argv, int fd);
char **mx_source(char *str);
int mx_fg(char **args, int fd);
bool mx_check_dir_exists(char *dir);
int mx_set(char **argv, int fd);
