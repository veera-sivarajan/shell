# include "parse.h"

# define RL_BUFSIZE 1024
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a\0"

char **split_line (char *line) {
    if (strlen(line) == 0) {
        return NULL;
    }
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
    free(token);
    tokens[position] = NULL;
    return tokens;
}
