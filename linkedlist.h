# include <stdio.h>
# include <stdlib.h>

typedef struct node {
    char *word;
    struct node *next;
} node;

node *create_node (char *word);

void list_add (node **head, char *word);

void list_print (node *head);
