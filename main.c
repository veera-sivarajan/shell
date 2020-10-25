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

int execute(char **args) {
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
        printf("> ");
        line = read_line();
        args = split_line(line); 
        status = execute(args);

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
