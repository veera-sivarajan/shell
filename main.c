# include "parse.h"
# include "execute.h"
# include "hashtable.h"
# include "aliases.h"
# include <string.h>

# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

           
void input_loop(void) {
    char *line;
    char cwd[1024];
    char **args;
    int status;                 // get input and call necessary function to 
                                // execute the command
    do {
        getcwd(cwd, sizeof(cwd));
        printf(RED "%s> " RESET, cwd);
        line = read_line();
        args = split_line(line); 
        if (is_alias(args[0])) {
            char *value = (char *) malloc(100);
            value = get_command(args[0]);
            char buf[strlen(value)];
            strcpy(buf, value);
            args = split_line(buf);
            // execute_command(temp);
        }
        printf("ARGS: %s\n", args[0]);
        printf("ARGS: %s\n", args[1]);
        status = execute_command(args);
        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    load_aliases();
    insert_alias("lock", "loginctl lock-session");
    insert_alias("books", "okular sujatha.pdf"); 
    input_loop();
    return EXIT_SUCCESS;
}
