# include "parse.h"

# define RL_BUFSIZE 1024
# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a\0"

// splits a given string literal into words using strtok()
// returns a double pointer to a list of words
// NOTE returned value must be freed
char **split_line (char *line) {
    if (strlen(line) == 0) { // return NULL if user hits enter
        return NULL;
    }
    int bufsize= TOK_BUFSIZE;
    int position = 0;
    char **tokens = calloc(bufsize, sizeof(char *)); // sizeof(char *) == 8
    if (!tokens) {
        fprintf(stderr, "split_line: tokens malloc error\n");
        exit(EXIT_FAILURE);
    }
    char *token;
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

void split_pipe (char *input, pipeline *cmd_table) {
    int i = 0;
    char *split = strtok(input, "|");
    // printf("%s\n", split);
    cmd_table->cmd[i] = (char *) malloc(100);
    strcpy(cmd_table->cmd[i], split);
    while ((split = strtok(NULL, "|")) != NULL) {
        i += 1;
        // printf("%s\n", ++split);
        cmd_table->cmd[i] = (char *) malloc(100);
        strcpy(cmd_table->cmd[i], ++split);
    }
    cmd_table->cmd[i] = NULL;
    cmd_table->num_cmds = (i + 1);
    // printf("i: %i\n", i + 1);
}
