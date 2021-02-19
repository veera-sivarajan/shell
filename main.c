# include "execute.h"
# include "builtin.h"
# include <string.h>
          
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define SIZE 1024

int parse (elem **table, char *input) {
    int input_fd = 0;
    int pipe_fd[2];
    if (input == NULL) { // exit on C-d (EOF Character)
        exit(EXIT_SUCCESS);
    }
    if (input[0] != '\0') { // don't evaluate string when user press enter
        add_history(input);
        pipeline *cmd_table = (pipeline *) calloc(1000, sizeof(pipeline));
        cmd_table->cmd = (char **) malloc(100 * sizeof(char *));
        split_pipe(input, cmd_table);
        for (int i = 0; i <= cmd_table->num_cmds; ++i) {
            // printf("%s\n", cmd_table->cmd[i]);
            pipe(pipe_fd);
            evaluate(table, cmd_table->cmd[i]);
            free(cmd_table->cmd[i]);
        }
        free(cmd_table->cmd);
        free(cmd_table);
        free(input);
    }
}

// FIXME: alias_handler() should return the string to be executed
// input string are not null terminated
int evaluate (elem **table, char *input) {
    char *exec_string = NULL;
    char **args = NULL;
    int status = 1;  
    args = split_line(input);
    if (args != NULL) {
        // if (is_alias(table, input)) { // check if string is an alias
        //     // status = alias_handler(table, args);
        //     strcpy(exec_string, alias_handler(table, args));
        // }
        // else if (is_builtin(args)) { // check if command is a builtin
        //     status = builtin_handler(table, args);
        // }
        // else { // execute the command
        status = execute_command(args);
        // }
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
    int status = 0;
                    
    do {
        strcpy(cmd, BLUE);
        strcpy(reset, RESET);  // colorize current working directory path 
        getcwd(cwd, sizeof(cwd));
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$$ "); // append "$$" to colorized path 
        line = readline(cmd); // get user input with line editing 
        status = parse(table, line);
    } while (status); 
}

int main (int argc, char **argv) {
    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    using_history();
    if (read_history("history.txt")) {
        fprintf(stderr, "read history error\n");
    }
    printf("Hello, %s\n", getenv("USER")); // greeting message
    // pointer pointing to a list of alias elements
    // FIXME: alias should be accessed only from builtin.c
    // elem **table = (elem **) calloc(NUM_ELE, sizeof(elem *));
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
