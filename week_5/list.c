#include <stdio.h>
#include <stdlib.h>

// here im creating a struct that has a number (value), and the a node that points to the next struct, so that it creates a link list
typedef struct node
{
    int number;
    struct node *next;
} node;

//i will define a function that takes some arguments and converts them to a linked list, in which we will start with the first and then append the next onto the first place (the order of input will be reversed in the output)
int main (int argc, char *argv[])
{
    node *list = NULL; // we asign a null value as a starter of the linked list to avoid having a garbage value pointing already somewhere else
    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]); // we have to convert it to a number because the command line arguments are strings / char
        node *n = malloc(sizeof(node)); // i define a node called n, and i allocate memory to it (the size of a node)
        if (n == NULL)
        {
            // free memory thus far
            return 1;
        }
        n->number = number; // go to the value part of n and store the number (that comes from the argv)
        n->next = list; // this way we add the numbers to the existing linked list (which we started with a null value earlier). In the first adittion, this is equal to null, so the linked list has only one node, and then later we update the list value to hold the current pointer (so, x pointer to a value, the value and null)

        list = n; // now list is equal to the node, and with each iteration, list will be updated with the next argv, and the "next" part of the node will be pointing to the previous existing node. This way we have updated the list to the recently added node
    }
    // now onto the printing part after making the linked list, we create a pointer called ptr, and we put in its address the list we created (that beggins with the pointer to the first value/number)
    node *ptr = list;
    // now since we are going to keep jumping from a pointer to the next value and then to its pointer and so on, we create a loop that will finish when we reach the end of the linked list (also, we wont want to modify the original list)
    while (ptr != NULL)
    {
        // then we are printing the number in the node we created (the first one of the node)
        printf("%i\n", ptr->number);
        // after that, the ptr is asigned to the pointer that moves as to the next node, and then the loop keeps running if that pointer is not NULL
        ptr = ptr->next;
    }
}

// appending a number to the linked list runs in O(1) linear, as the number of nodes are irrelevant to the running time, but opposedly searching for something in the list runs in O(n), since we have as much steps as the nodes in the list (also, we cant use binary search, since the spaces in memory for a linked list are not contiguous, it wont know where its middle is)


