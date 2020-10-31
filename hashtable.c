# include <stdio.h>

# define PR_ONE 54059
# define PR_TWO 76963 
# define PR_THREE 86969 
# define FIRST 37

unsigned long
hash_function (char *word) {
    unsigned num = FIRST;
    while (*word) {
        num = (num * PR_ONE) ^ (word[0] * PR_TWO);
        word++;
    }
    return num % PR_THREE;
}

int main () {
    printf("Result: %li\n", hash_function("lock") % 10);
    printf("Result: %li\n", hash_function("clear") % 10);
    printf("Result: %li\n", hash_function("187") % 10);
    printf("Result: %li\n", hash_function("clears") % 10);
    return 0;
}
