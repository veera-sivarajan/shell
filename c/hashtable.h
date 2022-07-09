# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct alias_struct { 
    char *alias;
    char *command;
    int index;
} elem;

unsigned long hash_function (char *word);

elem *create_ele (elem **table, char *alias, char *command);

void insert_ele (elem **table, char *alias, char *command);

elem *get_ele (elem **table, char *alias);

void free_table (elem **table);


