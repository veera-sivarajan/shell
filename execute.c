# include "execute.h"
# include "builtin.h"
# include <signal.h>

# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

void handle_sigint(int sig) {
    printf("HANDLING SIGINT: %i\n", sig);
}

int start_process (char **args) {
    pid_t pid, wpid;
    int status;
    
    pid = fork();
    
    if (pid == 0) {
        // Child process
        // char *filename = args[0]; // a.k.a program name
        if (execvp(args[0], args) == -1) {
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
            if (wpid == -1) {
                perror("waitpid error");
                exit(EXIT_FAILURE);
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        // status is a pointer to the location where status information for
        // terminating process is stored
        // WUNTRACED - return if a child has stopped (but not traced via ptrace)
        // WIFEXITED - returns true if child terminated normally
        // WIFSIGNALED - return true if child terminated by signal
    }
    return 1;
}

int execute_command (char **args) {
    if (args == NULL) {
        // Empty command was entered
        return 1;
    }

    for (int i = 0; i < get_num_builtins(); ++i) {
        if (strcmp(args[0], all_builtin[i]) == 0) {
            return (*builtin_func[i]) (args);
        }
    }
    return start_process(args);
}
