# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct alias_struct { 
    char *alias;
    char *command;
    int index;
} elem;

unsigned long hash_function (char *word);

void load_aliases ();

elem *create_alias (char *alias, char *command);

void insert_alias (char *alias, char *command);

char *get_command (char *alias);

void free_table (void);


