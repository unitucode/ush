#include "ush.h"

static t_list *get_process_by_cmd(char *arg, t_list *processes) {
    t_list *ret_process = NULL;
    unsigned int count_processes = 0;
    t_process *tmp = NULL;

    while (processes) {
        tmp = (t_process*)processes->data;
        if (!mx_get_substr_index(tmp->cmd, arg)) {
            count_processes++;
            ret_process = processes;
        }
        processes = processes->next;
    }
    if (count_processes == 1)
        return ret_process;
    else if (count_processes > 1)
        fprintf(stderr, "fg: %s: ambiguous job spec\n", arg);
    else if (!count_processes)
        fprintf(stderr, "fg: %s: no such job\n", arg);
    return NULL;
}

static t_list *get_process_by_id(char *arg, t_list *processes) {
    int cur_pos = atoi(arg);
    t_process *tmp = NULL;

    while (processes) {
        tmp = (t_process*)processes->data;
        if (tmp->pos == cur_pos) {
            return processes;
        }
        processes = processes->next;
    }
    fprintf(stderr, "fg: %s: no such job\n", arg);
    return NULL;
}

static t_list *get_process(char *arg) {
    bool is_num = true;
    unsigned int len = 0;
    t_list **processes = mx_get_list_procs();

    if (!arg)
        return mx_get_last_process(*processes);
    arg++;
    len = strlen(arg);
    for (unsigned int i = 0; i < len; i++) {
        if (!isnumber(arg[i])) {
            is_num = false;
            break;
        }
    }
    if (is_num)
        return get_process_by_id(arg, *processes);
    else
        return get_process_by_cmd(arg, *processes);
}

static bool check_args(char **args) {
    if (!mx_arr_size(args))
        return true;
    if (mx_arr_size(args) > 1) {
        fprintf(stderr, "fg: too many arguments\n");
        return false;
    }
    if (args[0][0] != '%' || !args[0][1]) {
        fprintf(stderr, "fg: invalid argument: %s\n", args[0]);
        return false;
    }
    return true;
}

int mx_fg(char **args, int fd) {
    t_list *process = NULL;
    t_process *f_process = NULL;
    t_list **all_processes = mx_get_list_procs();

    if (!check_args(args))
        return 1;
    process = get_process(args[0]);
    if (process) {
        f_process = (t_process*)process->data;
        mx_disable_canon();
        tcsetpgrp(STDOUT_FILENO, f_process->gpid);
        mx_continue_process(f_process, all_processes, fd);
        tcsetpgrp(STDOUT_FILENO, getpgrp());
        mx_enable_canon();
    }
    else {
        fprintf(stderr, "%s", *args ? "" : "fg: no current jobs\n");
        return 1;   
    }
    return f_process->status;
}
