# include "execute.h"
# include "builtin.h"
# include "hashtable.h"
# include "aliases.h"
# include "parse.h"

int start_process(char **args) {
    printf("Inside start_process()\n");
    printf("RESULT: %s\n", args[0]);
    printf("RESULT: %s\n", args[1]);
    pid_t pid, wpid;
    int status;

    pid = fork();

    if (pid == 0) {
        // Child process
        char *filename = args[0]; // a.k.a program name
        if (execvp(filename, args) == -1) {
            perror("start_process execvp error");
        }
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) {
        // Error forking
        perror("fork() unsuccesul");
    }
    else {
        // Parent Process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        // status is a pointer to the location where status information for
        // terminating process is stored
        // WUNTRACED - return if a child has stopped (but not traced via ptrace)
        // WIFEXITED - returns true if child terminated normally
        // WIFSIGNALED - return true if child terminated by signal
    }
    return 1;
}

int execute_command(char **args) {
    if (args[0] == NULL) {
        // Empty command was entered
        return 1;
    }
    printf("Value: %s\n", args[0]);
    printf("Value: %s\n", args[1]);

    for (int i = 0; i < get_num_builtins(); ++i) {
        if (strcmp(args[0], all_builtin[i]) == 0) {
            return (*builtin_func[i]) (args);
        }
        // else if (strcmp(args[0], all_aliases[i]) == 0) {
        //     // char **temp = split_command(get_command(args[0]));
        //     // printf("Executing: %s\n", temp[0]);
        //     // return start_process(&temp[0]);
        //     char *result = get_command(args[0]);
        //     // printf("Size: %li\n", strlen(result));
        //     // char buf[strlen(result) + 1];
        //     // strcpy(buf, result);
        //     // char **try = split_line(buf);
        //     return split_command(result);
        //     // return start_process(try);
        // }
    }
    return start_process(args);
}
