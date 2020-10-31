# include "aliases.h"

char *all_aliases[] = {
    "lock",
    "cl",
    "prj",
    "books"
};

char **split_command(char *command) {
    char buff_array[strlen(command)];
    strcpy(buff_array, command);
    return split_line(buff_array);
}

