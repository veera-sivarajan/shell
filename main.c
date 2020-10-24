# include <stdio.h>
# include <stdlib.h>

# define RL_BUFSIZE 1024

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
    int count = 5;
    while (count) {
        printf("> ");
        line = read_line();
        free(line);
        count -= 1;
    }
}

int main(int argc, char **argv) {
    temp_input_loop();
    return EXIT_SUCCESS;
}
