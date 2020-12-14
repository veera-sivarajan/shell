# include "builtin.h"
# include "execute.h"



/*
  Function declarations for builtin shell commnads:
*/


char *all_builtin[] = {
    "cd",
    "help",
    "exit"
};

int (*builtin_func[]) (char **) = {
    &change_dir,
    &help_cmd,
    &exit_cmd
};


int get_num_builtins() {
    return sizeof(all_builtin) / sizeof(char *);
}

// char prev_dir[1024] = {};

int change_dir (char **args) {
    char prev_dir[1024];
    getcwd(prev_dir, sizeof(prev_dir));
    if (args[1] == NULL) {
        if (chdir(getenv("HOME")) != 0) {
            perror("chdir to home error");
        }
    }
    else if (*args[1] == '-') {
        if (chdir(getenv("OLDPWD")) != 0) {
            perror("cd - error\n");
        }
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("chdir error");
        }
    }
    setenv("OLDPWD", prev_dir, 1);
    return 1;
}

int help_cmd (char **args) {
    printf("List of built-in commands:\n");
    for (int i = 0; i < get_num_builtins(); ++i) {
        printf(" %s\n", all_builtin[i]);
    }
    printf("Use man command for information on other programs.\n");
    return 1;
}

int exit_cmd (char **args) {
    return 0;
}
