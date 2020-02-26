#include "ush.h"

static void copy_environ(char **copy, char **environ) {
    for (int i = 0; environ[i]; i++) {
        copy[i] = strdup(environ[i]);
        if (environ[i + 1] == NULL)
            copy[i + 1] = NULL;
    }
}

char **mx_env_copy(void) {
    extern char **environ;
    char **env_copy = NULL;
    int len = 0;

    while (environ[len]) {
        len++;
    }
    if (environ[0]) {
        env_copy = malloc((len + 1) * sizeof(char*));
        copy_environ(env_copy, environ);
    }
    return env_copy;
}
