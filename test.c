# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <stdlib.h>

void main () {
    while (1) {
        char *line = readline("Input: ");
        printf("Line: %s\n", line);
        if (strcmp(line, "exit") == 0) {
            break;
        }
    }
    exit(1);
}
