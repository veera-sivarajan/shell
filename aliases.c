# include "aliases.h"
# include "execute.h"

// char *all_aliases[] = {  // FIXME: alias names should be stored dynamically
//     "edlab",
//     "ls",
//     "lock",                        
//     "books",
//     "prj"
// };

node *alist = NULL;

void alist_add (char *word) {
    list_add(&alist, word);
}

char **split_command (char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

int get_num_aliases () {
    return 5;
}

int is_alias (char *word) {
    node *temp = alist;
    while (temp != NULL) {
        if (strcmp(word, temp->word) == 0) {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}

int alias_handler (char *alias) {
    char *command = get_command(alias);
    printf("Command: %s\n", command);
    printf("Executing: %s\n", command);
    char buf[strlen(command)];
    strcpy(buf, command);
    // return split_line(buf);
    return execute_command(split_line(buf));
}
