# include <stdio.h>
# include <string.h>
# include "parse.h"
# include "linkedlist.h"

extern char *all_aliases[]; 

void alist_add (char *word);

char **split_command(char *command);

int get_num_aliases();

int is_alias (char *word);

int alias_handler (char *alias);


