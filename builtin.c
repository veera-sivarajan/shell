# include "builtin.h"
# include "execute.h"



/*
  Function declarations for builtin shell commnads:
*/


char *all_builtin[] = {
    "cd",
    "help",
    "exit",
    "lock",
};

int (*builtin_func[]) (char **) = {
    &change_dir,
    &help_cmd,
    &exit_cmd,
    &lock_cmd,
};

int get_num_builtins() {
    return sizeof(all_builtin) / sizeof(char *);
}

int lock_cmd(char **args) {
    char **temp = malloc(3 * sizeof(char *));
    temp[0] = "loginctl";
    temp[1] = "lock-session";
    temp[2] = NULL;
    start_process(temp);
}

int change_dir(char **args) {
    if (args[1] == NULL) {
        // fprintf(stderr, "chage_dir: not enough arguments\n");
        if (chdir("/home/veera") != 0) {
            perror("chdir to home error");
        }
    }
    else {
        if (chdir(args[1]) != 0) {
            perror("chdir error");
        }
    }
    return 1;
}

int help_cmd(char **args) {
    printf("List of built-in commands:\n");
    for (int i = 0; i < get_num_builtins(); ++i) {
        printf(" %s\n", all_builtin[i]);
    }
    printf("Use man command for information on other programs.\n");
    return 1;
}

int exit_cmd(char **args) {
    return 0;
}
