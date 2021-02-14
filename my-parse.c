# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "parse.h" 

# include <readline/readline.h>
# include <readline/history.h>
char **pipe_parser (char *input) {
    char **result = (char **) calloc(1000, sizeof(char *)); 
    int num_cmds = 0; 
    int index = 0;
    result[0] = (char *) malloc(100);
    size_t size = strlen(input);
    for (int i = 0; i < size; ++i) {
        if (input[i] == '|') {
            // result[num_cmds][index] = '\0';
            num_cmds += 1;
            result[num_cmds] = (char *) malloc(100);
            index = 0;
        }
        else {
            if (index == 0 && input[i] == ' ') {
                continue;
            }
            result[num_cmds][index] = input[i];
            index += 1;
        }
    }
    // for (int i = 0; result[i] != NULL; ++i) {
    //     free(result[i]);
    // }
    // free(result);
    return result;
}

void split_pipe (char *input) {
    char *split = strtok(input, "|");
    while (split != NULL) {
        printf("%s\n", split);
        split = strtok(NULL, "|");
    }
}

// void parse_wrapper (char *input) {
//     char **cmd_list = pipe_parser(input);
//     for (int i = 0; cmd_list[i] != NULL; ++i) {
//         char **result = split_line(cmd_list[i]);
//         printf("COMMAND\n");
//         for (int i = 0; result[i]; ++i) {
//             printf("  String: %s\n", result[i]);
//         }
//         free(result);
//         free(cmd_list[i]);
//     }
//     free(cmd_list);
// }

int main (void) {
    // parse_wrapper("ls | cat");
    // parse_wrapper("git log --format='%an' | uniq -c");
    // char **result = split_line("git log --format='%an' | uniq -c");
    // char *input = readline(">> ");
    // char **result = pipe_parser(input);
    // for (int i = 0; i < 2; ++i) {
    //     printf("%s\n", result[i]);
    //     free(result[i]);
    // }
    // free(input);
    // free(result);
    char *input = readline(">> ");
    split_pipe(input);
    free(input);
    return 0;
}
        
