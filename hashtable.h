# include <stdio.h>
# include <stdlib.h>

typedef struct element {
    char *alias;
    char *command;
} elem;

unsigned long hash_function (char *word);

void load_aliases();

void insert_alias(char *alias, char *command);

char *get_command(char *alias);


