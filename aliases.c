# include "aliases.h"
# include "execute.h"

// char *all_aliases[] = {  // FIXME: alias names should be stored dynamically
//     "edlab",
//     "ls",
//     "lock",                        
//     "books",
//     "prj"
// };

char *all_aliases[10];
int num_aliases = 0;

void add_alias (char *word) {
    all_aliases[num_aliases] = word;
    num_aliases += 1;
}

char **split_command (char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

int get_num_aliases () {
    return num_aliases;
}

int is_alias (char *word) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        if (strcmp(word, all_aliases[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void print_aliases (elem **table) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        printf("%s = \"%s\"\n", all_aliases[i], get_command(table, all_aliases[i]));
    }
}

int alias_handler (elem **table, char *alias) {
    char *temp = alias;
    char *command = get_command(table, temp);
    char buf[strlen(command)];
    strcpy(buf, command);
    // return split_line(buf);
    return execute_command(split_line(buf));
}

void insert_alias (elem **table, char *alias, char *command) {
    add_alias(alias);
    insert_ele(table, alias, command);
}

char *get_command (elem **table, char *alias) {
    return get_ele(table, alias);
}
