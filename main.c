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
    char **args = NULL;
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
        if (line[0] != '\0') {
            add_history(line);  
            args = split_line(line);
            if (args != NULL) {
                if (is_alias(table, line)) {
                    status = alias_handler(table, args);
                }
                else if (is_builtin(args)) {
                    status = builtin_handler(table, args);
                }
                else {
                    status = execute_command(args);
                }
            }
            free(args);
        }
        free(line);
    } while (status);
}

int main (int argc, char **argv) {
    printf("Hello, %s\n", getenv("USER"));
    elem **table = (elem **) calloc(NUM_ELE, sizeof(elem *));
    if (!table) {
        fprintf(stderr, "hashtable: malloc error\n");
        exit(EXIT_FAILURE);
    }
    insert_alias(table, "p", "pwd");
    insert_alias(table, "lock", "loginctl lock-session");
    insert_alias(table, "ls", "ls --color"); 
    insert_alias(table, "edlab", "ssh vsivarajan@elnux.cs.umass.edu");
    // FIXME: this alias causes valgrind "Invalid read" error
    // insert_alias(table, "make", "make -k"); 
    input_loop(table);
    free_table(table);
    free(table);
    return EXIT_SUCCESS;
}
