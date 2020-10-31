# include <stdio.h>
# include <string.h>

# define TOK_DELIM " \t\r\n\a"

int main () {
    char *word = "loginctl lock-session";
    char buf[strlen(word)];
    strcpy(buf, word);
    char *token = strtok(buf, TOK_DELIM); 
}
