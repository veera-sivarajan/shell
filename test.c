# include <stdio.h>
# include <string.h>

char **split_command(char *variable) {
    char buf[strlen(variable)];
    strcpy(buf, variable);
    return split_line(buf);
}

int main () {
    
