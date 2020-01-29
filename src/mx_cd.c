#include "ush.h"

static int check_flag(char *flag, char *newdir);
static int change_dir(char *newdir);
static int do_flags(int flag, char *newdir);

int mx_cd(char *input) {
    char **split = mx_strsplit(input, ' ');
    int flag_code;

    mx_printstr("========\n");
    for (int i = 0; split[i]; i++)
        mx_printstr(split[i]);
    mx_printstr("\n========\n");

    if (input == NULL || mx_strcmp(input, "~") == 0) {
        change_dir(input);
        return 0;
    }
    if (split[2] != NULL) {
        fprintf(stderr, "cd: too many arguments");
        mx_del_strarr(&split);
        return 0;
    }
    flag_code = check_flag(split[0], split[1]);
    if (flag_code == -1)
        fprintf(stderr, "cd: string not in pwd: %s\n", split[0]);
    else if (flag_code == 0 && split[2]) {
   //     change_in_pwd(split[0], split[1]);
        return 0;
    }
    change_dir(split[0]);
    mx_del_strarr(&split);
    return 0;
}

static int check_flag(char *flag, char *newdir) {
    if ((mx_strcmp(flag, "-sP") || mx_strcmp(flag, "-P")) == 0) {
        do_flags(1, newdir);
        return 1;
    }
    if ((mx_strcmp(flag, "-Ps") || mx_strcmp(flag, "-s")) == 0) {
        do_flags(2, newdir);
        return 2;
    }
    if (mx_strcmp(flag, "-") == 0) {
        do_flags(3, newdir);
        return 3;
    }
    if (flag[0] == '-')
        return -1;
    if (mx_strcmp(flag, "/") == 0) {
        change_dir(NULL);
        change_dir("../..");
        return 4;
    }
    return 0;
}

static int change_dir(char *newdir) {
    int result;
    if (newdir == NULL)
        result = chdir(getenv("HOME"));
    else
        result = chdir(newdir);
    
    if (result < 0) {
        fprintf(stderr, "cd: %s: No such file or directory.\n", newdir);
    }
//
    char dir[1024];
    getcwd(dir, 1024);
    mx_printstr(dir);
    mx_printstr("\n");
//
    return result;
}

/*void change_in_pwd(char *str, char *str_to_change) {

}*/

static int do_flags(int flag, char *newdir) {
    char buf[1024];
    int result;
    char *newdir_slash = mx_strjoin("/", newdir);

    if (flag == 1) {
        result = readlink(mx_strjoin(getenv("PWD"), newdir_slash), buf, 1024);
        result = (result == -1) ? change_dir(newdir) : change_dir(buf);
    }
    if (flag == 2) {
        
    }
    if (flag == 3)
        result = change_dir(NULL);
    mx_strdel(&newdir_slash);
    return result;
}
