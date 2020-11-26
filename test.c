# include <stdio.h>
# include <string.h>

int main () {
    char *string = "123456789";
    char buf[5];
    strncpy(buf, string, 5);
    printf("BUF: %s\n", buf);
}
    
