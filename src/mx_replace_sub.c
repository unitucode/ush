#include "ush.h"

static void append(char **result, char *buf) {
    char *tmp_str = mx_strjoin(*result, buf);

    mx_strdel(result);
    *result = mx_strdup(tmp_str);
    mx_strdel(&tmp_str);
}

char *mx_get_output_fd(int fd) {
    size_t bytes = 0;
    char *output = NULL;
    char buf[128];

    while ((bytes = read(fd, buf, sizeof(buf) - 1)) > 0) {
        buf[bytes] = '\0';
        append(&output, buf);
    }
    return output;
}

static char *get_output(char **arguments, unsigned int len) {
    int fds[2];
    char *output = NULL;
    char *save = NULL;

    pipe(fds);
    mx_exec_fork(arguments, fds[1]);
    close(fds[1]);
    output = mx_get_output_fd(fds[0]);
    close(fds[0]);
    if (output) {
        save = output;
        output = mx_strtrim(output);
        mx_strdel(&save);
        if (strlen(output) + len > ARG_MAX - 1)
            return NULL;
    }
    return output;
}

static void parse_commands(char **commands, char *sub, char *arg, int *code) {
    char **arguments = NULL;
    char *output = NULL;

    for (unsigned int i = 0; commands[i]; i++) {
        if (!(arguments = mx_interpretate(commands[i], code))) {
            mx_del_strarr(&commands);
            mx_strdel(&sub);
            continue;
        }
        output = get_output(arguments, strlen(arg));
        if (output) {
            strcat(arg, output);
            mx_strdel(&output);
        }
        mx_del_strarr(&arguments);
    }
}

bool mx_get_sub(char *arg, char *sub, int *code) {
    char **commands = NULL;
    bool sub_type = true;

    if (sub[0] == '$')
        sub_type = false;
    if (mx_remove_subchar(sub))
        commands = mx_parse_command(sub, code);
    if (*code || !commands)
        return false;
    if (sub_type)
        mx_replace_sub_escapes(commands);
    parse_commands(commands, sub, arg, code);
    mx_strdel(&sub);
    mx_del_strarr(&commands);
    return true;
}
