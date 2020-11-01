# include "aliases.h"

char *all_aliases[] = {
    "lock",
    "cl",
    "prj",
    "books"
};

char **split_command(char variable[100]) {
    char **try = split_line(variable);
    printf("Split_command: %s\n", try[0]);
    printf("Split_command: %s\n", try[1]);
    return try;
}
