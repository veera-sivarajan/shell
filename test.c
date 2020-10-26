# define _GNU_SOURCE 
# include <stdio.h>
# include <stdlib.h> 
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

int main() {
    char *p[] = {"loginctl", "lock-session"};
    // char **temp = malloc(3 * sizeof(char *)); 
    char *temp[3];
    temp[0] = "loginctl";
    temp[1] = "lock-session";
    temp[2] = NULL;
    // int out;
    // int pid = fork();
    // int status, wpid;
    // if (pid == 0) {
    //     out = execvp(p[0], p);
    // }
    // else if (pid > 0) {
    //     do {
    //         wpid = waitpid(pid, &status, WUNTRACED);
    //     } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    // }
    // printf("Result: %i\n", out);
    printf("Result: %s\n", *(temp+1));
    return 0;
}
