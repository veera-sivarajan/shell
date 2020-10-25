# include <stdio.h>
# include <stdlib.h> 
# include <errno.h>
# include <unistd.h>

int main(int argc, char **argv) {
    chdir(argv[1]);
}
