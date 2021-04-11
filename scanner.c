# include "scanner.h"
# include <stdlib.h>

# define NUM_COMMANDS 5
# define CMD_SIZE 100

// readline input is not new line terminated 

typedef struct Command_Table {
    char *command;
    char **args;
} table;

int is_lower_alpha (char input_char) {
    return (input_char >= 97 && input_char <= 122);
}

void scan_line (char *input) {
    table **all_commands = (table **) malloc(NUM_COMMANDS * sizeof(table));
    int input_length = strlen(input);
    int curr_pos = 0;
    int cmd_index = 0;
    
    while (curr_pos < input_length) {
        char curr_char = input[curr_pos];
        if (is_lower_alpha(curr_char)) {
            char *command = (char *) calloc(20 , CMD_SIZE);
            while (curr_char != ' ' && curr_pos < input_length) {
                strncat(command, &curr_char, 1);
                curr_pos += 1;
                curr_char = input[curr_pos];
            }
            all_commands[cmd_index] = (table *) malloc(1 * sizeof(table));
            all_commands[cmd_index]->command = (char *) malloc(100);
            strcpy(all_commands[cmd_index]->command, command);
            printf("Command: %s\n", command);
            free(command);
            free(all_commands[0]->command);
        } else if (curr_char == '-') {
            char *args = (char *) calloc(20, CMD_SIZE);
            while (curr_char != ' ' && curr_pos < input_length) {
                strncat(args, &curr_char, 1);
                curr_pos += 1;
                curr_char = input[curr_pos];
            }
            // all_commands[cmd_index]->args = (char
            printf("Args: %s\n", args);
            free(args);
        } else {
            switch (curr_char) {
            case ' ':
                printf("Space Character\n");
                curr_pos += 1;
                break;
            case '|':
                printf("Pipe Character: %c\n", curr_char);
                curr_pos += 1;
                break;
            case '>':
                if (input[++curr_pos] == '>') {
                    printf("Great Great Character\n"); 
                    curr_pos += 1;
                    break;
                }
                else {
                    printf("Great Character: %c\n", curr_char);
                    break;
                }
                curr_pos += 1;
            }
        }
    }
    free(input);
    free(all_commands[0]);
    free(all_commands);
}
