#include "ush.h"

static unsigned int get_count_commands(char *commands);
static unsigned int get_next_command(char *command);

char **mx_split_commands(char *command) {
    unsigned int c_commands = get_count_commands(command);
    char **commands = malloc(sizeof(char *) * (c_commands + 1));
    unsigned int index = 0;
    unsigned int last_word = 0;

    commands[c_commands] = NULL;
    for (unsigned int i = 0; i < c_commands; i++) {
        index = get_next_command(command);
        commands[i] = strndup(command, index);
        last_word = index + 1;
        command += last_word;
    }
    return commands;
}


static unsigned int get_next_command(char *command) {
    bool s_q = false;
    bool g_a = false;
    
    for (unsigned int i = 0; command[i]; i++) {
        if (command[i] == ';' && !s_q && !g_a)
            return i;
        if (!command[i + 1] && command[i] != ';')
            return i + 1;
        if (command[i] == MX_S_QUOTE) {
            if (i > 1 && command[i - 1] == '\\' && command[i - 2] != '\\')
                continue;
            if (i == 1 && command[i - 1] == '\\')
                continue;
            s_q = !s_q;
        }
        if (command[i] == MX_GRAVE_ACCENT && !s_q)
            g_a = !g_a;
    }
    return 0;
}

static unsigned int get_count_commands(char *command) {
    bool s_q = false;
    bool g_a = false;
    unsigned int result = 0;

    for (unsigned int i = 0; command[i]; i++) {
        if ((command[i] == ';' && !s_q && !g_a) || !command[i + 1])
            result++;
        if (command[i] == MX_S_QUOTE) {
            if (i > 1 && command[i - 1] == '\\'
                && command[i - 2] != '\\') {
                continue;
            }
            if (i == 1 && command[i - 1] == '\\')
                continue;
            s_q = !s_q;
        }
        if (command[i] == MX_GRAVE_ACCENT && !s_q)
            g_a = !g_a;
    }
    return result;
}
