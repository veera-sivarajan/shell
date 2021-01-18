# include "aliases.h"
# include "execute.h"

# define BUF_SIZE 50 
# define NUM_ALIAS 10 

int alias_indexes[NUM_ALIAS];
int num_aliases = 0;

void add_alias (elem **table, char *word) {
    elem *temp = get_ele(table, word);
    alias_indexes[num_aliases] = temp->index;
    // printf("Hash: %i at index: %i\n", temp->index, num_aliases);
    num_aliases++;
}

char **split_command (char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

int get_num_aliases () {
    return num_aliases;
}

int is_alias (elem **table, char **word) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        if ((strcmp(word[0], table[alias_indexes[i]]->alias) == 0)) {
                return 1;
        }
    }
    return 0;
}

void print_aliases (elem **table) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        printf("%s = \"%s\"\n", table[alias_indexes[i]]->alias, get_command(table, table[alias_indexes[i]]->alias));
    }
}

int alias_handler (elem **table, char **args) {
    char *command = get_command(table, args[0]);
    int size = strlen(command);
    // for (int i = 1; args[i]; ++i) {
    //     size += strlen(args[i]);
    // }
    // char buf[size * 2];
    char buf[size];
    // printf("SIZE OF BUF: %i\n", size);
    strcpy(buf, command);
    // for (int i = 1; args[i]; ++i) {
    //     strcat(buf, " ");
    //     strcat(buf, args[i]);
    // }
    // buf[strlen(buf) + 1] = '\0';
    return execute_command(split_line(buf));
}

void insert_alias (elem **table, char *alias, char *command) {
    insert_ele(table, alias, command);
    add_alias(table, alias);
}

char *get_command (elem **table, char *alias) {
    elem *temp = get_ele(table, alias);
    return temp->command;
}
