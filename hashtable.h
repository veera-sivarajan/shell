# include <stdio.h>
# include <stdlib.h>

typedef struct element {
    char *alias;
    char *command;
    int index;
} elem;

unsigned long hash_function (char *word);


