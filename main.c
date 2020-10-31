# include "parse.h"
# include "execute.h"
# include "hashtable.h"
# include "aliases.h"

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
        status = execute_command(args);

        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    load_aliases();
    insert_alias("lock", "loginctl lock-session");
    input_loop();
    return EXIT_SUCCESS;
}
