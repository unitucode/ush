#include "ush.h"

static int check_flag(char *flag, char *newdir);
static int change_dir(char *newdir);
static void do_flags(int flag, char *newdir);
static void cd_second_part(char **split, int flag_code);

int mx_cd(char **split) {
    int flag_code;

    if (split == NULL || (mx_strcmp(split[0], "~") && !split[1]) == 0) {
        change_dir(split[0]);
        return 0;
    }
    flag_code = check_flag(split[0], split[1]);
    if (flag_code < 1 || flag_code > 4)
        cd_second_part(split, flag_code);
    return 0;
}

static int check_flag(char *flag, char *newdir) {
    if (mx_strcmp(flag, "-sP") == 0 || mx_strcmp(flag, "-P") == 0) {
        do_flags(1, newdir);
        return 1;
    }
    if (mx_strcmp(flag, "-Ps") == 0 || mx_strcmp(flag, "-s") == 0) {
        do_flags(2, newdir);
        return 2;
    }
    if (mx_strcmp(flag, "-") == 0) {
        change_dir(getenv("OLDPWD"));
        return 3;
    }
    if (flag[0] == '-')
        return -1;
    if (mx_strcmp(flag, "/") == 0) {
        change_dir(flag);
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
/*
    char dir[1024];
    getcwd(dir, 1024);
    mx_printstr(dir);
    mx_printstr("\n");
*/
    return result;
}

void cd_second_part(char **split, int flag_code) {
    if (flag_code == -1) {
        fprintf(stderr, "cd: string not in pwd: %s\n", split[0]);
        return;
    }
    else if (flag_code == 0 && split[2]) {                                    
        change_dir(split[0]);
        return;                                                             
    }                                                                         
    change_dir(split[0]);
    return;
}

static void do_flags(int flag, char *newdir) {
    char buf[PATH_MAX];
    int result = 0;
    char *newdir_slash = mx_strjoin("/", newdir);
    char *newdir_link;

    newdir_link = mx_strjoin(getenv("PWD"), newdir_slash);
    if (flag == 1) {
        result = readlink(newdir_link, buf, PATH_MAX);
        result = (result == -1) ? change_dir(newdir) : change_dir(buf);
    }
    if (flag == 2) {
        
    }
    mx_strdel(&newdir_link);
    mx_strdel(&newdir_slash);
    return;
}
