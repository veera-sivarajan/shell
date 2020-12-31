# include "hashtable.h" 

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37
# define NUM_ELE 10 

int index_list[100];
int count = 0;

unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    return num % PR_THREE;
}

// void load_table () {
//     int num_aliases = NUM_ELE;
//     table = calloc(num_aliases, sizeof(elem));
//     if (!table) {
//         fprintf(stderr, "load_aliases: table mallocation error\n");
//         exit(EXIT_FAILURE);
//     }
// }

elem *create_ele (elem **table, char *alias, char *command) {
    elem *temp = (elem *) malloc(sizeof(elem));
    temp->alias = alias;
    temp->command = command;
    unsigned long index = hash_function(alias);
    index %= NUM_ELE;
    while (table[index] != NULL) {
        index++;
    }
    temp->index = index;
    index_list[count++] = index;
    return temp;
}

void insert_ele (elem **table, char *alias, char *command) {
    elem *temp = create_ele(table, alias, command);
    table[temp->index] = temp;
}

char *get_ele (elem **table, char *alias) {    
    unsigned long address = hash_function(alias);
    address %= NUM_ELE;
    while (1) {
        if (strcmp(table[address]->alias, alias) == 0) {
            // printf("RETURNING %s\n", table[address]->command);
            return table[address]->command;
        }
        address++;
    }
}

// void free_table (void) {
//     for (int i = 0; i < count; ++i) {
//         free(table[index_list[i]]);
//     }
//     free(table);
// }

