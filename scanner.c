# include "scanner.h"
# include <stdlib.h>

# define NUM_COMMANDS 5
# define CMD_SIZE 100

// readline input is not new line terminated 

typedef struct Command_Table {
    char *command;
    char **args;
} command_table;

command_table commands[NUM_COMMANDS];

int is_lower_alpha (char input_char) {
    return (input_char >= 97 && input_char <= 122);
}

typedef enum Redirect_Tokens {
    SPACE_TOKEN,
    PIPE_TOKEN,
    GREAT_TOKEN,
    GREATGREAT_TOKEN
} redirect_tokens;
    

void scan_line (char *input) {
    int input_length = strlen(input);
    int current_pos = 0;
    while (current_pos < strlen(input)) {
        if (is_lower_alpha(input[current_pos])) {
            printf("Lower alphabet: %c\n", input[current_pos]);
            char *command = (char *) calloc(20 , CMD_SIZE);
            while (input[current_pos] != ' ' && current_pos < strlen(input)) {
                strncat(command, &input[current_pos], 1);
                current_pos += 1;
                // if (current_pos > input_length) return;
            }
            printf("First Command: %s\n", command);
            free(command);
        }
        else {
            switch (input[current_pos]) {
            case ' ':
                printf("Space Character: \n");
                current_pos += 1;
                break;
            case '|':
                printf("Pipe Character: %c\n", input[current_pos]);
                current_pos += 1;
                break;
            case '>':
                if (input[++current_pos] == '>') {
                    printf("Great Great Character\n"); 
                    current_pos += 1;
                    break;
                }
                else {
                    printf("Great Character: %c\n", input[current_pos]);
                    break;
                }
                current_pos += 1;
            }
        }
    }
    free(input);
}
