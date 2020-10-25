# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define RL_BUFSIZE 1024
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

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

// void input_loop(void) {
//     char *line;
//     char **args;
//     int status;                 // get input and call necessary function to 
//                                 // execute the command
//     do {
//         printf("> ");
//         line = read_line();
//         // args = split_line(line); 
//         // status = execute(args);

//         free(line);
//         // free(args);
//     } while (status);
// }

void temp_input_loop(void) {
    char *line;
    char **args;
    int count = 5;
    while (count) {
        printf("> ");
        line = read_line();
        args = split_line(line);
        char **temp = args;
        while (*temp) {
            printf("Token: %s\n", *temp);
            temp += 1;
        }
        free(line);
        free(args);
        count -= 1;
    }
}

int main(int argc, char **argv) {
    temp_input_loop();
    return EXIT_SUCCESS;
}
