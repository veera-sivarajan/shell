# define _GNU_SOURCE
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>

# define RL_BUFSIZE 1024
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"
# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

int start_process(char **args) {
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
/*
  Function declarations for builtin shell commnads:
*/

int change_dir(char **args);
int help_cmd(char **args);
int exit_cmd(char **args);

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

int change_dir(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "chage_dir: not enough arguments\n");
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

int execute_command(char **args) {
    if (args[0] == NULL) {
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
           
char **split_line(char *line) {
    int bufsize= TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *)); // sizeof(char *) == 8
    char *token;

    if (!tokens) {
        fprintf(stderr, "split_line: tokens mallocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOK_DELIM);

    while (token != NULL) {
        tokens[position] = token;
        position += 1;

        if (position >= bufsize) {
            bufsize += TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "split_line: reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

char *read_line(void) {
    int bufsize = RL_BUFSIZE;
    int position = 0;
    char *buffer = (char *) malloc(bufsize);
    int input_char;

    if (!buffer) {
        fprintf(stderr, "read_line: buffer allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        input_char = getchar();

        if (input_char == EOF || input_char == '\n') {
            buffer[position] = '\0';
            return buffer;
        }

        else {
            buffer[position] = input_char;
        }
        position += 1;

        if (position >= bufsize) {
            bufsize += RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "read_line: buffer reallocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void input_loop(void) {
    char *line;
    char **args;
    int status;                 // get input and call necessary function to 
                                // execute the command
    do {
        printf(RED "%s> " RESET, get_current_dir_name());
        line = read_line();
        args = split_line(line); 
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}

// void temp_input_loop(void) {
//     char *line;
//     char **args;
//     int count = 3;
//     while (count) {
//         printf("> ");
//         line = read_line();
//         args = split_line(line);
//         char **temp = args;
//         while (*temp) {
//             printf("Token: %s\n", *temp);
//             temp += 1;
//         }
//         free(line);
//         free(args);
//         count -= 1;
//     }
// }

int main(int argc, char **argv) {
    input_loop();
    return EXIT_SUCCESS;
}
