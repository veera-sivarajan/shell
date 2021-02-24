# include "builtin.h"
          
# include <readline/readline.h>
# include <readline/history.h>

# define RESET "\x1B[0m"
# define BLUE "\e[1;34m"
# define SIZE 1024
# define NUM_ELE 100 

// FIXME: alias_handler() should return the string to be executed
// input string are not null terminated
int evaluate (elem **table, char *input, FD *fdescs) {
    char **args = NULL;
    int status = 1;  
    args = split_line(input);
    if (args != NULL) {
        if (is_alias(table, input)) { // check if string is an alias
            status = alias_handler(table, args, fdescs);
        }
        else if (is_builtin(args)) {
            status = builtin_handler(table, args);
        }
        // printf("Exec string: %s\n", exec_string);
        else {
            status = execute_command(args, fdescs);
        }
    }
    free(args);
    free(input);
    return status;
}

// typedef struct file_descriptors {
//     int input_fd;
//     int pipe_fd[2];
// } FD;

int parse (elem **table, char *input) {
    FD *fdescs = (FD *) malloc (10 * sizeof(FD)); 
    fdescs->input_fd = 0; // first process reads input from stdin == 0
    int result = 0;
    int i;
    if (input == NULL) { // exit on C-d (EOF Character)
        exit(EXIT_SUCCESS);
    }
    if (input[0] != '\0') { // don't evaluate string when user press enter
        add_history(input);
        pipeline *cmd_table = (pipeline *) calloc(1000, sizeof(pipeline));
        cmd_table->cmd = (char **) malloc(100 * sizeof(char *));
        split_pipe(input, cmd_table);
        printf("NUM_CMDS: %i\n", cmd_table->num_cmds);
        for (i = 0; i < cmd_table->num_cmds - 1; ++i) {
            // printf("%s\n", cmd_table->cmd[i]);
            pipe(fdescs->pipe_fd);
            printf("EVALUATING: %s\n", cmd_table->cmd[i]);
            result = evaluate(table, cmd_table->cmd[i], fdescs);
            close(fdescs->pipe_fd[1]);
            fdescs->input_fd = fdescs->pipe_fd[0];
        }
        if (fdescs->input_fd != 0) {
            dup2(fdescs->input_fd, 0);
        }
        result = evaluate(table, cmd_table->cmd[i], fdescs);
        free(fdescs);
        free(cmd_table->cmd);
        free(cmd_table);
        free(input);
    }
    return result;
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
