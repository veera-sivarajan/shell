# include <stdio.h>
# include <string.h>
# include "parse.h"
# include "hashtable.h"

void add_alias (elem **table, char *word);

char **split_command (char *command);

int get_num_aliases ();

int is_alias (elem **table, char **word);

void print_aliases (elem **table);

int alias_handler (elem **table, char *alias);

void insert_alias (elem **table, char *alias, char *command);

char *get_command (elem **table, char *alias);

void free_aliases (void);
