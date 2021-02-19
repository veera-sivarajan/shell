# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct command_struct {
    char **cmd;
    int num_cmds;
} pipeline;

char **split_line(char *line);

char *read_line(void);

void split_pipe (char *input, pipeline *cmd_table);
