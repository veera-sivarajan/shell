# include "aliases.h"
# include "execute.h"

char *all_aliases[] = {
    "lock",
    "cl",
    "prj",
    "books"
};

int split_command(char *variable) {
    printf("Size: %ld\n", strlen(variable));
    char buf[strlen(variable)];
    strcpy(buf, variable);
    for (int i = 0; buf[i] != '\0'; ++i) {
        printf("%c ", buf[i]);
    }
    printf("\n");
    char **value = split_line(buf);
    start_process(value);
    // return value;
}
