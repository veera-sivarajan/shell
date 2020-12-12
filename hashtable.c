# include "hashtable.h" 

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37
# define NUM_ELE 10 

elem **table;

unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    return num % PR_THREE;
}

void load_aliases () {
    int num_aliases = NUM_ELE;
    table = calloc(num_aliases, sizeof(elem));
    if (!table) {
        fprintf(stderr, "load_aliases: table mallocation error\n");
        exit(EXIT_FAILURE);
    }
}

// void insert_alias (char *alias, char *command) {
//     // printf("Entering insert_alias\n");
//     unsigned long index = hash_function(alias);
//     index %= NUM_ELE;
//     while (table[index].command != NULL) {
//         index++;
//     }
//     // printf("Inserting values...\n");
//     // printf("Exit insert_alias\n");
//     printf("Index of alias: %li\n", index);
//     table[index].alias = (char *) malloc(100);
//     table[index].alias = alias;
//     table[index].command = (char *) malloc(100);
//     table[index].command = command;
// }

elem *create_alias (char *alias, char *command) {
    elem *temp = (elem *) malloc(sizeof(elem));
    temp->alias = alias;
    temp->command = command;
    unsigned long index = hash_function(alias);
    index %= NUM_ELE;
    while (table[index] != NULL) {
        index++;
    }
    temp->index = index;
    return temp;
}

void insert_alias (char *alias, char *command) {
    elem *temp = create_alias(alias, command);
    table[temp->index] = temp;
}
    
// FIXME: fetches value from incorrect index becuase
//        index != actual index of command
char *get_command (char *alias) {    
    unsigned long address = hash_function(alias);
    address %= NUM_ELE;
    while (1) {
        if (strcmp(table[address]->alias, alias) == 0) {
            return table[address]->command;
        }
        address++;
    }
    
    
}

