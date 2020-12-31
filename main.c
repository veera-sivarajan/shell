# include "parse.h"
# include "execute.h"
# include "builtin.h"
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# define RESET "\x1B[0m"
# define RED   "\x1B[31m"
# define NUM_ELE 10 

void input_loop (elem **table) {
    char *line;
    char cwd[1024];
    char **args;
    int status;                 // get input and call necessary function to 
                                // execute the command
    do {
        char cmd[1024] = "\e[1;34m";
        char reset[1024] = "\x1B[0m";
        getcwd(cwd, sizeof(cwd));
        strcat(cmd, cwd);
        strcat(cmd, reset);
        strcat(cmd, "$ ");
        line = readline(cmd);
        add_history(line);
        args = split_line(line);
        if (is_alias(line)) {
            status = alias_handler(table, line);
        }
        else if (is_builtin(args)) {
            status = builtin_handler(table, args);
        }
        else {
            status = execute_command(args);
        }
        free(line);
    } while (status);
}

int main (int argc, char **argv) {
    printf("Hello, %s\n", getenv("USER"));
    // load_table();
    elem **table = calloc(NUM_ELE, sizeof(elem));
    insert_alias(table, "cl", "cd /home/veera");
    insert_alias(table, "lock", "loginctl lock-session");
    insert_alias(table, "books", "okular sujatha.pdf"); 
    insert_alias(table, "edlab", "ssh vsivarajan@elnux.cs.umass.edu");
    char *hello[2] = { "ls", "ls --color=auto" };
    insert_alias(table, hello[0], hello[1]);
    input_loop(table);
    return EXIT_SUCCESS;
}
