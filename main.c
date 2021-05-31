# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include "lexer.h"
# include <string.h>
          
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define RED "\x1b[31m"
# define NUM_ELE 100 
# define SIZE 1024

typedef struct command_struct {
    char **command;
    int num_cmds;
} command;


void split_pipe (char *input, command *cmd_table) {
    int i = 0;
    char *split = strtok(input, "|");
    // printf("%s\n", split);
    cmd_table->command[i] = (char *) malloc(100);
    strcpy(cmd_table->command[i], split);
    while ((split = strtok(NULL, "|")) != NULL) {
        i += 1;
        // printf("%s\n", ++split);
        cmd_table->command[i] = (char *) malloc(100);
        strcpy(cmd_table->command[i], ++split);
    }
    cmd_table->num_cmds = i;
}

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
    // free(input);
    return status;
}

// shell REPL gets user input and calls necessary function to
// execute the command
void input_loop (elem **table) {
    char *input_line;
    char cwd[SIZE];
    char cmd[SIZE];
    char reset[SIZE];
    int status = 0;
    command *cmd_table = (command *) calloc(1000, sizeof(command));
    cmd_table->command = (char **) malloc(100 * sizeof(char *));
                    
    do {
        getcwd(cwd, sizeof(cwd));
        strcpy(cmd, BLUE);
        strcpy(reset, RESET);  // colorize current working directory path 
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$$ "); // append "$$" to colorized path 
        input_line = readline(cmd); // get user input with line editing 
        if (strcmp(input_line, "exit") == 0) {
            free(input_line);
            break;
        }
        if (strlen(input_line) == 0) {
            free(input_line);
            status = 1;
            continue;
        }
        // add_history(line);
        // status = evaluate(table, line);
        // scan_line(line);
        split_pipe(input_line, cmd_table);
        printf("Num commands: %i\n", cmd_table->num_cmds);
        for (int i = 0; i <= cmd_table->num_cmds; ++i) {
            // printf("%s\n", cmd_table->command[i]);
            status = evaluate(table, cmd_table->command[i]);
            free(cmd_table->command[i]);
        }
        free(input_line);
    } while (status); 
    free(cmd_table->command);
    free(cmd_table);
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
    rl_clear_history();
    
    
    free_table(table);
    free(table);
    return EXIT_SUCCESS;
}
