# include "parse.h"
# include "execute.h"
# include "aliases.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# define RESET "\x1B[0m"
# define RED   "\x1B[31m"

// int stupid_function (char *line, char *word) {
//     printf("Word: %s\n", line);
//     printf("Word: %s\n", word);
//     char *pointer_array[2] = { *line, *word };
//     for (int i = 0; pointer_array[i] != NULL; ++i) {
//         printf("POINTER; %s\n", pointer_array[i]);
//     }
//     return 0;
// }

           
void input_loop(void) {
    char *line;
    char cwd[1024];
    char **args;
    int status;                 // get input and call necessary function to 
                                // execute the command
    do {
        getcwd(cwd, sizeof(cwd));
        // line = read_line();
        // printf("%s", cwd);
        strcat(cwd, RED "> " RESET);
        line = readline(cwd);
        // printf("LINE: %s\n", line);
        // args = split_line(line); 
        if (is_alias(line)) {
            // args = alias_handler(line);
            // status = stupid_function(args[0], args[1]);
            status = alias_handler(line);
        }
        else {
            args = split_line(line); 
            status = execute_command(args);
            free(args);
        }
        free(line);
    } while (status);
}

int main(int argc, char **argv) {
    printf("Hello, %s\n", getenv("USER"));
    load_aliases();
    // insert_alias("cl", "cd /home/veera/Classes/Fall20/"); 
    insert_alias("prj", "cd /home/veera");
    insert_alias("lock", "loginctl lock-session");
    insert_alias("books", "okular sujatha.pdf"); 
    input_loop();
    return EXIT_SUCCESS;
}
