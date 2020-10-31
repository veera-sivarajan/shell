# include "hashtable.h" 

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37
# define TABLE_BUFSIZE 100


unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    return num % PR_THREE;
}

elem *load_aliases() {
    elem *table = calloc(TABLE_BUFSIZE, sizeof(elem));
    if (!table) {
        fprintf(stderr, "load_aliases: table mallocation error\n");
        exit(EXIT_FAILURE);
    }
}

void insert_alias(elem *table, char *alias, char *command) {
    unsigned long index = hash_function(alias);
    index %= 100;
    table[index].command = command;
}

char *get_command(elem *table, char *alias) {
    unsigned long index = hash_function(alias);
    index %= 100;
    return table[index].command;
}

int main () {
    insert_alias(table, "lock", "loginctl lock-session");
    printf("Result: %s\n", get_command(table, "lock"));
    return 0;
}
