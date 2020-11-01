# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/wait.h>
# include "hashtable.h"

# define TOK_DELIM " \t\r\n\a"

char **split_line(char *line) {
    int bufsize= 64;
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
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "split_line: reallocation error\n");
                exit(1);
            }
        }

        token = strtok(NULL, TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}

int start_process(char **args) {
    printf("Inside start_process()\n");
    printf("RESULT: %s\n", args[0]);
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

char **split_command(char *variable) {
    printf("Size: %s\n", strlen(variable));
    char **try = split_line(variable);
    printf("Split_command: %s\n", try[0]);
    printf("Split_command: %s\n", try[1]);
    return try;
}

int main () {
    load_aliases();
    insert_alias("lock", "loginctl lock-session");
    char *command = get_command("lock");
    printf("Command: %c\n", command[0]);
    int i;
    for (i = 0; command[i] != '\0'; ++i) {
        printf("%c ", command[i]);
    }
    printf("\n");
    command[i] = '\0';
    printf("Number: %c\n", command[i]);
}
