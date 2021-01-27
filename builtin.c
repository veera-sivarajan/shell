# include "builtin.h"
# include "execute.h"

/*
  Function declarations for builtin shell commnads:
*/

// list of pointers to all builtin commands
char *all_builtin[] = {
    "cd",
    "help",
    "exit",
    "export"
};


// function pointers to all builtin commands' function
int (*builtin_func[]) (char **) = {
    &change_dir,
    &help_cmd,
    &exit_cmd,
    &export_cmd,
};

// return total number of builting commands
int get_num_builtins() {
    return sizeof(all_builtin) / sizeof(char *);
}

// check if first element in passed value is a builtin command
int is_builtin (char **words) {
    if (words == NULL) {
        return 0;
    }
    int size = get_num_builtins();
    for (int i = 0; i < size; ++i) {
        if ((strcmp(words[0], all_builtin[i]) == 0) || (strcmp(words[0], "alias") == 0)) {
            return 1;
        }
    }
    return 0;
}

// evaluates a builtin command entered by user
// TODO alias should be handled in a seperate function 
int builtin_handler (elem **table, char **args) {
    int result;
    int num_builtins = get_num_builtins();
    for (int i = 0; i < num_builtins; ++i) {
        if (strcmp(args[0], "alias") == 0) { // alias command
            if ((args[1] != NULL) && (args[2] != NULL)) { // user adds new alias
                insert_alias(table, args[1], args[2]);
                result = 1;
                break;
            }
            else {
                print_aliases(table); // list all aliases
                result = 1;
                break;
            }
        }
        
        // compare user entered builtin with all builtin commands
        // and call the necessary function
        else if (strcmp(args[0], all_builtin[i]) == 0) {
            result = (*builtin_func[i]) (args);        
            break;
        }
    }
    return result;
}

# define PATH_SIZE 256
// function to change directory
// TODO Add error handling for number of arguments more than one 
int change_dir (char **args) {
    char prev_dir[PATH_SIZE];
    getcwd(prev_dir, sizeof(prev_dir));
    if (args[1] == NULL) { // change directory to $HOME
        if (chdir(getenv("HOME")) != 0) {
            perror("chdir to home error");
        }
    }
    else if (args[1][0] == '~') { // append arguments to $HOME and cd into it 
        char path[PATH_SIZE];
        strcpy(path, getenv("HOME"));
        strcat(path, ++args[1]);
        if (chdir(path) != 0) {
            perror("cd ~ error\n");
        }
    }
    else if (*args[1] == '-') { // change directory to previous directory
        char *dir = getenv("OLDPWD");
        printf("%s\n", dir);
        if (chdir(dir) != 0) {
            perror("cd - error\n");
        }
    }
    else { // change directory to user entered path
        if (chdir(args[1]) != 0) {
            perror("chdir error");
        }
    }
    setenv("OLDPWD", prev_dir, 1); // update previous directory env variable
    return 1;
}

// list all builtin commands 
int help_cmd (char **args) {
    printf("List of built-in commands:\n");
    for (int i = 0; i < get_num_builtins(); ++i) {
        printf(" %s\n", all_builtin[i]);
    }
    printf("Use man command for information on other programs.\n");
    return 1;
}

// end the shell process
int exit_cmd (char **args) {
    return 0;
}

int export_cmd (char **args) {
    setenv(args[1], args[2], 1);
    return 1;
}
