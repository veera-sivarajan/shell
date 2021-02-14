# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include "parse.h" 

# include <readline/readline.h>
# include <readline/history.h>

void split_pipe (char *input) {
    char *split = strtok(input, "|");
    printf("%s\n", split);
    while ((split = strtok(NULL, "|")) != NULL) {
        printf("%s\n", ++split);
    }
}

int main (void) {
    char *input = readline(">> ");
    split_pipe(input);
    free(input);
    return 0;
}
        
