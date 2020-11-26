# include "parse.h"
# include "execute.h"
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
        printf("%s> ", cwd);
        line = read_line();
        args = split_line(line); 
        if (is_alias(args[0])) {
            alias_handler(args[0]);
            // printf("ALIAS COMMAND\n");
            // char *value = (char *) malloc(100);
            // value = get_command(args[0]);
            // printf("VALUE: %s\n", value);
            // char buf[strlen(value)];
            // strcpy(buf, value);
            // printf("BUFFER:\n");
            // for (int i = 0; buf[i] != '\0'; ++i) {
            //     printf("%c", buf[i]);
            // }
            // printf("\n");
            // args = split_line(buf);
            // printf(RED "INSIDE input_loop()\n" RESET);
            // for (int i = 0; i < 3; ++i) {
            //     printf("args[%i]: %s\n", i, args[i]);
            // }
            // // execute_command(temp);
        }
        status = execute_command(args);
        free(line);
        free(args);
    } while (status);
}

int main(int argc, char **argv) {
    load_aliases();
    insert_alias("boomba", "echo lock"); 
    insert_alias("lock", "loginctl lock-session");
    insert_alias("books", "okular sujatha.pdf"); 
    input_loop();
    return EXIT_SUCCESS;
}
