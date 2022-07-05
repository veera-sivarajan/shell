# include "lexer.h"
# include <stdlib.h>

# define NUM_COMMANDS 5
# define CMD_SIZE 100

// readline input is not new line terminated 

typedef struct Command_Table {
    int num_args;
    char **args;
} Command_Table ;

int is_lower_alpha (char input_char) {
    return (input_char >= 97 && input_char <= 122);
}

// should free the input
void scan_line (char *input) {
    Command_Table **table = (Command_Table **) malloc(NUM_COMMANDS * sizeof(table));
    int input_length = strlen(input);
    int curr_pos = 0;
    int cmd_index = 0;
    int arg_num = 0;
    table[cmd_index] = (Command_Table *) malloc(100);
    table[cmd_index]->args = (char **) malloc(100);
    
    while (curr_pos <= input_length) {
        char curr_char = input[curr_pos];
        if (curr_char == '\0') {
            printf("Arg num: %i\n", arg_num);
            table[cmd_index]->num_args = arg_num;
            arg_num = 0;
            cmd_index += 1;
            table[cmd_index] = (Command_Table *) malloc(100);
            table[cmd_index]->args = (char **) malloc(100);
            break;
        } else if (is_lower_alpha(curr_char)) {
            char *command = (char *) calloc(20 , CMD_SIZE);
            while (curr_char != ' ' && curr_pos < input_length) {
                strncat(command, &curr_char, 1);
                curr_pos += 1;
                curr_char = input[curr_pos];
            }
            // table[cmd_index]->cmds[arg_num] = (char *) malloc(100);
            // strcpy(table[cmd_index]->cmds[arg_num], command);
            printf("Copying at.. table %i and args %i\n", cmd_index, arg_num);
            table[cmd_index]->args[arg_num] = (char *) malloc(100);
            strcpy(table[cmd_index]->args[arg_num], command);
            arg_num += 1; 
            // printf("Command #: %i\n", cmd_index);
            // printf("Command: %s\n", command);
            free(command);
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
                // printf("Space Character\n");
                curr_pos += 1;
                break;
            case '|':
                // printf("Pipe Character: %c\n", curr_char);
                printf("Arg num: %i\n", arg_num);
                table[cmd_index]->num_args = arg_num;
                arg_num = 0;
                cmd_index += 1;
                table[cmd_index] = (Command_Table *) malloc(100);
                table[cmd_index]->args = (char **) malloc(100);
                curr_pos += 1;
                break;
            case '>':
                if (input[++curr_pos] == '>') {
                    printf("Great Great Character\n"); 
                    curr_pos += 1;
                    break;
                } else {
                    printf("Great Character: %c\n", curr_char);
                    break;
                }
                curr_pos += 1;
                break;
            default:
                printf("Unknown character\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    // printf("Arg num: %i\n", arg_num);
    // table[cmd_index]->num_args = arg_num;
    // for (int i = 0; i <= cmd_index; ++i) {
    //     printf("Arg num: %s\n", table[i]->args[0]);
    //     free(table[i]->args);
    //     free(table[i]);
    // }
    free(input);
    free(table);
}
