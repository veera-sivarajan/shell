# define _GNU_SOURCE 
# include <stdio.h>
# include <stdlib.h> 
# include <errno.h>
# include <unistd.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

int main() {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("Result: %s\n", cwd);
}
