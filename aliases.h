# include <stdio.h>
# include <string.h>
# include "parse.h"
# include "hashtable.h"

void add_alias (elem **table, char *word);

char **split_command (char *command);

int get_num_aliases ();

int is_alias (elem **table, char *line);

void print_aliases (elem **table);

void alias_handler (elem **table, char **args, char *exec_string);

void insert_alias (elem **table, char *alias, char *command);

char *get_command (elem **table, char *alias);
