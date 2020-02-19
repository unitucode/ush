#include "ush.h"

static char *get_output(char **arguments, unsigned int len);
static void append(char **result, char *buf);

bool mx_get_sub(char *arg, char *sub, int *code) {
    char **arguments = NULL;
    char *output = NULL;
    char **commands = NULL;

    if (mx_remove_subchar(sub)) {
        commands = mx_parse_command(sub, code);
    }
    if (*code || !commands)
        return false;
    for (unsigned int i = 0; commands[i]; i++) {
        commands[i] = mx_replace_escape(commands[i], "\\\\",  '\\', true);
        commands[i] = mx_replace_escape(commands[i], "\\`", MX_GRAVE_ACCENT, true);
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
    mx_strdel(&sub);
    mx_del_strarr(&commands);
    return true;
}

static char *get_output(char **arguments, unsigned int len) {
    int fds[2];
    char *output = NULL;
    size_t bytes = 0;
    char buf[128];
    char *save = NULL;

    pipe(fds);
    mx_exec_command(arguments, fds[1]);
    close(fds[1]);
    while ((bytes = read(fds[0], buf, sizeof(buf) - 1)) > 0) {
        buf[bytes] = '\0';
        append(&output, buf);
    }
    close(fds[0]);
    if (output) {
        save = output;
        output = mx_strtrim(output);
        mx_strdel(&save);
        if (strlen(output) + len > ARG_MAX - 1) {
            return NULL;
        }
    }
    return output;
}

static void append(char **result, char *buf) {
    char *tmp_str = mx_strjoin(*result, buf);

    mx_strdel(result);
    *result = mx_strdup(tmp_str);
    mx_strdel(&tmp_str);
}
