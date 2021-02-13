# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "parse.h" 

char **pipe_parser (char *input) {
    char **result = (char **) malloc(1000 * sizeof(char *)); 
    int num_cmds = 0; 
    int index = 0;
    result[0] = (char *) malloc(100);
    for (int i = 0; i < strlen(input); ++i) {
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
    return result;
}

// void parse_wrapper (char *input) {
//     char **cmd_list = pipe_parser(input);
//     for (int i = 0; cmd_list[i] != NULL; ++i) {
//         // char **result = split_line(cmd_list[i]);
//         // printf("COMMAND\n");
//         // for (int i = 0; result[i]; ++i) {
//         //     printf("  String: %s\n", result[i]);
//         // }
//         // free(result);
//         free(cmd_list[i]);
//     }
//     free(cmd_list);
// }

int main (void) {
    // parse_wrapper("ls | cat");
    char **result = pipe_parser("git log --format='%an' | uniq -c");
    for (int i = 0; result[i] != NULL; ++i) {
        free(result[i]);
    }
    free(result);
    return 0;
}
        
