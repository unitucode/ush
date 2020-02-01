#include "ush.h"

static int change_dir(char *newdir);
static int check_on_flags(char *flag, char *newdir);

int mx_cd(char **split) {
    int flag;

    if (split == NULL)
        change_dir(NULL);
    if (check_on_flags(split[0], split[1]) == 0)
        change_dir(split[0]);
    return 1;
}



static int change_dir(char *newdir) {
    int result;
    char *result_path;

    if (newdir == NULL)
        result = chdir(getenv("HOME"));
    else if(mx_strcmp(newdir, "~OLDPWD")) {
        result = chdir(getenv("OLDPWD"));
        printf("%s\n", getenv("OLDPWD"));
    }
    else
        result = chdir(newdir);
    if (result < 0) {
        fprintf(stderr, "cd: %s No such file or directory.\n", newdir);
        return result;
    }
    result_path = mx_parse_path(mx_get_map("PWD"), newdir);
    mx_put_map(map, "OLDPWD", strdup(mx_get_map(map, "PWD")));
    mx_put_map(map, "PWD", result_path);
    mx_strdel(&result_path);
    return result;
}

static int check_on_flags(char *flag, char *newdir) {
    if (mx_strcmp(flag, "-P") == 0)
        do_on_flags(1, newdir);
    else if (mx_strcmp(flag, "-s") == 0)
        do_on_flags(2, newdir);
    else if (mx_strcmp(flag, "-") == 0 && newdir == NULL)
        change_dir(NULL);
    else if ((mx_strcmp(flag, "-") && newdir != NULL) || flag[0] == '-')
        fprintf(stderr, "cd: string not in pwd: %s\n", flag); 
    else if (mx_strcmp(flag, "/")) {
        change_dir(flag);
    else
        return 0;
    return 1;
}

static void do_on_flags(int flag, char *newdir) {
    char *newdir_path;
    char *newdir_path_real;

    newdir_path = mx_strjoin(getenv("PWD"), "/");
    newdir_path = strcat(newdir_path, newdir);
    newdir_path_real = realpath(newdir_path, NULL);
    if (flag == 1) {
        if (mx_strcmp(newdir_path, newdir_path_real) != 0) {

        }
    }
    else if (flag == 2) {
        if (mx_strcmp(newdir_path, newdir_path_real) != 0)
            fprintf(stderr, "cd: %s: is not a directory.\n", newdir);
        else
            change_dir(newdir);
    }
    mx_strdel(&newdir_path_real); 
    mx_strdel(&newdir_path);
}

// mx_get_map(map, "PWD");
//mx_put_map(map, strdup("PWD"), strdup(getenv("PWD")));                    
//mx_put_map(map, strdup("OLDPWD"), strdup(getenv("OLDPWD")))
