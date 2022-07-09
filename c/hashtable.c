# include "hashtable.h" 

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37
# define NUM_ELE 10 
# define MEM_SIZE 1000

int index_list[100]; // not sure why these global variables exist
int count = 0;

// returns hash value for given string
unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    num = (num % PR_THREE) % NUM_ELE;
    return num;
}

// creates a element which contains an alias, its command and its index 
// returns created element
// NOTE created element should be freed
elem *create_ele (elem **table, char *alias, char *command) {
    elem *temp = (elem *) malloc(sizeof(elem) * NUM_ELE);
    if (!temp) {
        fprintf(stderr, "create_ele: temp malloc error\n");
        exit(EXIT_FAILURE);
    }
    temp->alias = (char *) malloc(MEM_SIZE);
    if (!temp->alias) {
        fprintf(stderr, "create_ele: alias malloc error\n");
        exit(EXIT_FAILURE);
    }
    temp->command = (char *) malloc(MEM_SIZE);
    if (!temp->command) {
        fprintf(stderr, "create_ele: command malloc error\n");
        exit(EXIT_FAILURE);
    }
    strcpy(temp->alias, alias);
    strcpy(temp->command, command);
    unsigned long index = hash_function(alias);
    while (table[index] != NULL) {
        index++; // table is initialized with NULL because of calloc
    }
    temp->index = index;
    // index_list[count++] = index;
    return temp;
}

// create an alias element and store in table
void insert_ele (elem **table, char *alias, char *command) {
    elem *temp = create_ele(table, alias, command);
    table[temp->index] = temp;
}

// returns an alias element for given alias string
elem *get_ele (elem **table, char *alias) {    
    unsigned long address = hash_function(alias);
    // address %= NUM_ELE;
    while (1) { // FIXME: fetching an unknown alias will result in infinite loop
        if (table[address] != NULL) {
            if (strcmp(table[address]->alias, alias) == 0) {
                return table[address];
            }
        }
        address++;
    }
}

// free all elements in table 
void free_table (elem **table) {
    extern int alias_indexes[10]; 
    extern int num_aliases;
    for (int i = 0; i < num_aliases; ++i) {
        free(table[alias_indexes[i]]->alias);
        free(table[alias_indexes[i]]->command);
        free(table[alias_indexes[i]]);
    }
}

