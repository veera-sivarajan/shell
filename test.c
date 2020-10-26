# define _GNU_SOURCE 
# include <stdio.h>
# include <stdlib.h> 
# include <errno.h>
# include <unistd.h>
# include <limits.h>

int main() {
    char *p[] = {"loginctl", "lock-session", NULL};
    int out = execvp(p[0], p);
    printf("Result: %i\n", out);
    return 0;
}
