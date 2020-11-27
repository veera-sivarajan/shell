# include "aliases.h"
# include "execute.h"

char *all_aliases[] = {
    "lock",
    "cl",
    "prj",
    "books",
    "boomba"
};

char **split_command(char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

int get_num_aliases() {
    return sizeof(all_aliases) / sizeof(char *);
}

int is_alias(char *word) {
    int size = get_num_aliases();
    for (int i = 0; i < size; ++i) {
        if (strcmp(word, all_aliases[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

int alias_handler (char *alias) {
    int i, j;
    char *command = get_command(alias);
    char buf[strlen(command)];
    strcpy(buf, command);
    // return split_line(buf);
    return execute_command(split_line(buf));
}
