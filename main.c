# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include "scanner.h"
# include <string.h>
          
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define NUM_ELE 100 
# define SIZE 1024

/*
int parse (elem **table, char *input) {
    if (input == NULL) { // exit on C-d (EOF Character)
        exit(EXIT_SUCCESS);
    }
    if (input[0] != '\0') { // don't evaluate string when user press enter
        add_history(input);
        command *cmd_table = (command *) calloc(1000, sizeof(command));
        cmd_table->command = (char **) malloc(100 * sizeof(char *));
        split_pipe(input, cmd_table);
        for (int i = 0; i <= cmd_table->num_cmds; ++i) {
            // printf("%s\n", cmd_table->command[i]);
            evaluate(table, cmd_table->command[i]);
            free(cmd_table->command[i]);
        }
        free(cmd_table->command);
        free(cmd_table);
        free(input);
    }
}
*/

// input string are not null terminated
int evaluate (elem **table, char *input) {
    char **args = NULL;
    int status = 1;  
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
    int status = 1;
                    
    do {
        strcpy(cmd, BLUE);
        strcpy(reset, RESET);  // colorize current working directory path 
        getcwd(cwd, sizeof(cwd));
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$$ "); // append "$$" to colorized path 
        line = readline(cmd); // get user input with line editing 
        if (strcmp(line, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }
        // status = evaluate(table, line);
        scan_line(line);
    } while (status); 
}

int main (int argc, char **argv) {
    signal(SIGINT, SIG_IGN); // ignore sigint and sigtstp
    signal(SIGTSTP, SIG_IGN);
    using_history();
    if (read_history("history.txt")) {
        fprintf(stderr, "read history error\n");
    }
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
    insert_alias(table, "books", "cd ~/Books");
    insert_alias(table, "ff", "emacsclient -n");
    input_loop(table);
    // free all allocated memory
    if (append_history(1000, "history.txt")) {
        fprintf(stderr, "write history error\n");
    }
    clear_history();
    free_table(table);
    free(table);
    return EXIT_SUCCESS;
}
