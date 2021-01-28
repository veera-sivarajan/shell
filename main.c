# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define NUM_ELE 100 
# define SIZE 1024

int evaluate (elem **table, char *input) {
    char **args = NULL;
    int status = 1;  
    if (input == NULL) {  // exit on C-d (EOF character)
        exit(EXIT_SUCCESS);
    }
    if (input[0] != '\0') {
        add_history(input);  // add user input to command history 
        args = split_line(input);
        if (args != NULL) {
            if (is_alias(table, input)) { // check if string is an alias
                status = alias_handler(table, args);
            }
            else if (is_builtin(args)) { // check if command is a builtin
                status = builtin_handler(table, args);
            }
            else { // execute the command
                status = execute_command(args);
            }
        }
        free(args);
    }
    free(input);
    return status;
}

// shell REPL gets user input and calls necessary function to
// execute the command
void input_loop (elem **table) {
    char *line;
    char cwd[SIZE];
    char cmd[SIZE];
    char reset[SIZE];
    int status = 0;
                    
    do {
        strcpy(cmd, BLUE);
        strcpy(reset, RESET);  // colorize current working directory path 
        getcwd(cwd, sizeof(cwd));
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$$ "); // append "$$" to colorized path 
        line = readline(cmd); // get user input with line editing 
        status = evaluate(table, line);
    } while (status); 
}

int main (int argc, char **argv) {
    signal(SIGINT, SIG_IGN);
    printf("Hello, %s\n", getenv("USER")); // greeting message
    // pointer pointing to a list of alias elements
    elem **table = (elem **) calloc(NUM_ELE, sizeof(elem *));
    if (!table) {
        fprintf(stderr, "hashtable: malloc error\n");
        exit(EXIT_FAILURE);
    }
    // insert all alias
    insert_alias(table, "cl", "cd /home/veera/Classes/Fall20");
    insert_alias(table, "lock", "loginctl lock-session");
    insert_alias(table, "ls", "ls --color"); 
    insert_alias(table, "edlab", "ssh vsivarajan@elnux.cs.umass.edu");
    input_loop(table);
    // free all allocated memory
    free_table(table);
    free(table);
    return EXIT_SUCCESS;
}
