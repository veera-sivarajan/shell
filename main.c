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
            if (is_alias(table, args)) {
                status = alias_handler(table, line);
            }
            else if (is_builtin(args)) {
                status = builtin_handler(table, args);
            }
            else {
                status = execute_command(args);
            }
            free(args);
            free(line);
        }
    } while (status);
}

int main (int argc, char **argv) {
    printf("Hello, %s\n", getenv("USER"));
    elem **table = (elem **) calloc(NUM_ELE, sizeof(elem *));
    insert_alias(table, "cl", "cd /home/veera");
    insert_alias(table, "lock", "loginctl lock-session");
    insert_alias(table, "ls", "ls --color"); 
    insert_alias(table, "edlab", "ssh vsivarajan@elnux.cs.umass.edu");
    input_loop(table);
    free_table(table);
    // free_aliases();
    free(table);
    return EXIT_SUCCESS;
}
