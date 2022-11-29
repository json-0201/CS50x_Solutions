#include <stdio.h>
#include <stdlib.h>

// Typedef simplifies "struct node" -> "node"
// Data Type for a linked list
typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(void)
{
    //List of size, address of "list" with node datatype
    node *list = NULL;

    // Add a number to list, (tmp method)
    node *n = malloc(sizeof(node));
    if (n == NULL)
    {
        return 1;
    }
    n -> number = 1;
    n -> next = NULL;

    // Update list to point to new node
    list = n;

    // Add another number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list);
        return 1;
    }
    n -> number = 2;
    n -> next = NULL;
    list -> next = n;

    // Add a number to list
    n = malloc(sizeof(node));
    if (n == NULL)
    {
        free(list -> next);
        free(list);
        return 1;
    }
    n -> number = 3;
    n -> next = NULL;
    list -> next -> next = n;

    // Print numbers
    for (node *tmp = list; tmp != NULL; tmp = tmp -> next)
    {
        printf("%i\n", tmp -> number);
    }

    // Free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    return 0;
}