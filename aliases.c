# include "aliases.h"
# include "execute.h"

# define BUF_SIZE 50 
# define NUM_ALIAS 10 

// FIXME using global variables is not a good practice
//       global variables are poor man's parameters
int alias_indexes[NUM_ALIAS]; // array to store index of every alias
int num_aliases = 0; // total number of aliases

// store alias' index and increment total number of aliases
void add_alias (elem **table, char *word) {
    elem *temp = get_ele(table, word);
    alias_indexes[num_aliases] = temp->index;
    // printf("Hash: %i at index: %i\n", temp->index, num_aliases);
    num_aliases++;
}

// wrapper function for split_line()
// converts string literal to string array
char **split_command (char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

// returns total number of aliases
// not sure why it is a function
int get_num_aliases () {
    return num_aliases;
}

// check if passed alias is an existing alias
int is_alias (elem **table, char *alias) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        if ((strcmp(alias, table[alias_indexes[i]]->alias) == 0)) {
                return 1;
        }
    }
    return 0;
}

// print all aliased commands
void print_aliases (elem **table) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        printf("%s = \"%s\"\n", table[alias_indexes[i]]->alias,
               get_command(table, table[alias_indexes[i]]->alias));
    }
}

// FIXME: Should return a string instead of evaluating
// evaluates an alias entered by user
void alias_handler (elem **table, char **args, char *exec_string) {
    char *command = get_command(table, args[0]);
    char buf[50];
    // printf("SIZE OF BUF: %i\n", size);
    strcpy(buf, command);
    for (int i = 1; args[i]; ++i) { // add user arguments to alias command
        strcat(buf, " ");
        strcat(buf, args[i]);
    }
    buf[strlen(buf) + 1] = '\0';
    printf("alias_handler\n");
    strcpy(exec_string, buf);
    // printf("Exec_string: %s\n", exec_string);
    // char **split_command = split_line(buf);
    // int status = execute_command(split_command);
    // free(split_command);
    // return status;
}

// inserts a command into table at index equal to hash value of alias
void insert_alias (elem **table, char *alias, char *command) {
    if (!is_alias(table, alias)) { // Add only new alias 
        insert_ele(table, alias, command);
        add_alias(table, alias);
    }
    else {
        fprintf(stderr, "alias exists already\n");
    }
}

// returns the command for a given alias
char *get_command (elem **table, char *alias) {
    if (is_alias(table, alias)) {
        elem *temp = get_ele(table, alias);
        return temp->command;
    }
    return NULL;
}
