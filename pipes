# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>

typedef struct command_struct {
    char **command;
    int num_cmds;
} command;

void split_pipe (char *input, command *cmd_table) {
    int i = 0;
    char *split = strtok(input, "|");
    // printf("%s\n", split);
    cmd_table->command[i] = (char *) malloc(100);
    strcpy(cmd_table->command[i], split);
    while ((split = strtok(NULL, "|")) != NULL) {
        i += 1;
        // printf("%s\n", ++split);
        cmd_table->command[i] = (char *) malloc(100);
        strcpy(cmd_table->command[i], ++split);
    }
    cmd_table->num_cmds = i;
}

void parse_pipes (command *cmd_table) {
    int input_fd = 0;
    int pipes_fd[2];

    for (int i = 0; i <= cmd_table->num_cmds; ++i) {
        pipe(pipes_fd);
    }
}

// int main (void) {
//     command *cmd_table = (command *) calloc(1000, sizeof(command));
//     cmd_table->command = (char **) malloc(100 * sizeof(char *));
//     char *input = readline(">> ");
//     split_pipe(input, cmd_table);
//     // for (int i = 0; cmd_table->command[i] != NULL; ++i) {
//     for (int i = 0; i <= cmd_table->num_cmds; ++i) {
//         printf("%s\n", cmd_table->command[i]);
//         free(cmd_table->command[i]);
//     }
//     free(cmd_table->command);
//     free(cmd_table);
//     free(input);
//     return 0;
// }
        
