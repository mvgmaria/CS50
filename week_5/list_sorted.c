// Implements a sorted list of numbers using a linked list

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    // Memory for numbers
    node *list = NULL;

    // For each command-line argument
    for (int i = 1; i < argc; i++)
    {
        // Convert argument to int
        int number = atoi(argv[i]);

        // Allocate node for number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n->number = number;
        n->next = NULL;

        // If list is empty (it will be in the first iteration, so we will asign it the first node)
        if (list == NULL)
        {
            list = n;
        }

        // If number belongs at beginning of list (we compare it to the number, and it is smaller, we node's next to the first node of the list, and then we update the beggining of the list no the new node)
        else if (n->number < list->number)
        {
            n->next = list;
            list = n;
        }

        // If number belongs later in list
        else
        {
            // Iterate over nodes in list
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                // If already at end of list (cause list has only one node and the number is not less than that, then it will inevitably will belong to the last place)
                if (ptr->next == NULL)
                {
                    // Append node
                    ptr->next = n;
                    break;
                }

                // If we find ourselves in middle of list we will check if the number we are trying to append is smaller than the one we are in in the iteration, if not, we will keep iterating until we find the spot, and if we reach the end of the list, we will append it there 
                if (n->number < ptr->next->number)
                {
                    n->next = ptr->next;
                    ptr->next = n;
                    break;
                }
            }
        }
    }

    // Print numbers
    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->number);
    }

    // Free memory
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        free(ptr);
        ptr = next;
    }
}
