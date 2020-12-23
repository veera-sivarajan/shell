# include "builtin.h"
# include "execute.h"

/*
  Function declarations for builtin shell commnads:
*/

char *all_builtin[] = {
    "cd",
    "help",
    "exit",
    "alias"
};

int (*builtin_func[]) (char **) = {
    &change_dir,
    &help_cmd,
    &exit_cmd
};

int get_num_builtins() {
    return sizeof(all_builtin) / sizeof(char *);
}

int is_builtin (char *word) {
    int size = get_num_builtins();
    for (int i = 0; i < size; ++i) {
        if (strcmp(word, all_builtin[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int builtin_handler (elem **table, char *command) {
    char buf[strlen(command)];
    strcpy(buf, command);
    char **args = split_line(buf); 
    int result;
    for (int i = 0; i < get_num_builtins(); ++i) {
        if (strcmp(args[0], "alias") == 0) {
            print_aliases(table);
            result = 1;
            break;
        }
        else if (strcmp(args[0], all_builtin[i]) == 0) {
            return (*builtin_func[i]) (args);
        }
    }
    return result;
}

int change_dir (char **args) {
    char prev_dir[1024];
    getcwd(prev_dir, sizeof(prev_dir));
    if (args[1] == NULL) {
        if (chdir(getenv("HOME")) != 0) {
            perror("chdir to home error");
        }
    }
    else if (*args[1] == '-') {
        char *dir = getenv("OLDPWD");
        printf("%s\n", dir);
        if (chdir(dir) != 0) {
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
