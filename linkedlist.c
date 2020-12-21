# include "linkedlist.h"

node *create_node (char *word) {
    node *temp = (node *) malloc(sizeof(node));
    temp->word = word;
    temp->next = NULL;
    return temp;
}

void list_add (node **head, char *word) {
    node *temp = create_node(word);
    node **curr = head;
    while (*curr) {
        curr = &(*curr)->next;
    }
    *curr = temp;
}

void list_print (node *head) {
    while (head != NULL) {
        printf("%s\n", head->word);
        head = head->next;
    }
}

        
        
