#include "ush.h"

static void clear_data(char **s2, char ***a_s1, char ***a_s2) {
    mx_del_strarr(a_s1);
    mx_del_strarr(a_s2);
    mx_strdel(s2);
}

void mx_replace_sub_escapes(char **commands) {
    unsigned int i = 0;

    while (commands[i]) {
        commands[i] = mx_replace_escape(commands[i], "\\`",
                                        MX_GRAVE_ACCENT, true);
        commands[i] = mx_replace_escape(commands[i], "\\\\",  '\\', true);
        i++;
    }
}

bool mx_check_user(char *user_name) {
    DIR *dir = opendir("/Users/");
    struct dirent *entry;

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, user_name)) {
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    return false;
}

char *mx_check_user_file(char *tmp_name) {
    char *pass_file = mx_file_to_str("/etc/passwd");
    char **lines = mx_strsplit(pass_file, '\n');
    char **data = NULL;
    char *result = NULL;

    for (unsigned int i = 0; lines[i]; i++) {
        if (lines[i][0] != '#') {
            data = mx_strsplit(lines[i], ':');
            if (!strcmp(data[0], tmp_name)) {
                result = strdup(data[5]);
                clear_data(&pass_file, &data, &lines);
                return result;
            }
            mx_del_strarr(&data);
        }
    }
    mx_del_strarr(&lines);
    mx_strdel(&pass_file);
    return NULL;
}

char *mx_get_invalid_sub(char **arg, char **result, char **sub) {
    mx_strdel(arg);
    mx_strdel(result);
    mx_strdel(sub);
    return NULL;
}
