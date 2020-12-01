# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

void main () {
    char *buf = (char *) malloc(1024);
    int res = getlogin_r(buf, 100);
    printf("%s\n", buf);
}
