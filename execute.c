# include "execute.h"
# include "builtin.h"

# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

int start_process(char **args) {
    pid_t pid, wpid;
    int status;
    printf(RED "INSIDE START PROCESS\n" RESET);
    for (int i = 0; i < 3; ++i) {
        printf("args[%i]: %s\n", i, args[i]);
    }

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
    printf(RED "INSIDE execute_command\n" RESET);
    for (int i = 0; i < 3; ++i) {
        printf("args[%i]: %s\n", i, args[i]);
    }

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
