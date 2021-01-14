# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define NUM_ELE 10 
# define SIZE 1024

void input_loop (elem **table) {
    char *line;
    char cwd[SIZE];
    char cmd[SIZE];
    char reset[SIZE];
    char **args;
    int status = 1;                 // get input and call necessary function to 
                                // execute the command
    do {
        strcpy(cmd, BLUE);
        strcpy(reset, RESET);
        getcwd(cwd, sizeof(cwd));
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$$ ");
        line = readline(cmd);
        add_history(line);
        args = split_line(line);
        if (args) {
            if (is_alias(line)) {
                status = alias_handler(table, line);
            }
            else if (is_builtin(args)) {
                status = builtin_handler(table, args);
            }
            else {
                status = execute_command(args);
            }
            // printf("ENTERING FREEE AREANA\n");
            for (int i = 0; args[i]; ++i) {
                free(args[i]);
                printf("FREEING ARGS...\n");
            } 
            // // free(args);
        }
    } while (status);
}

int main (int argc, char **argv) {
    printf("Hello, %s\n", getenv("USER"));
    elem **table = calloc(NUM_ELE, sizeof(elem));
    insert_alias(table, "cl", "cd /home/veera");
    insert_alias(table, "lock", "loginctl lock-session");
    insert_alias(table, "books", "okular sujatha.pdf"); 
    insert_alias(table, "edlab", "ssh vsivarajan@elnux.cs.umass.edu");
    input_loop(table);
    extern char *all_aliases[10];
    printf("ENTERING MAIN FREE AREANA\n");
    int size = get_num_aliases();
    printf("SIZE: %i\n", size);
    for (int i = 0; i < size; ++i) {
        if (i != 1 && i != 3) {
            free(table[i]->alias);
            free(table[i]->command);
            printf("Freeing table element...%i\n", i);
        }
    }
    // printf("%s\n", table[1]->alias);
    printf("TABLE ELEMENTS FREED\n");
    free(table);
    return EXIT_SUCCESS;
}
