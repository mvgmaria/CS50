#include <cs50.h>
#include <stdio.h>

void meow(void); // it is enough to leave this line "the function's prototype", which has the right amount of information in order for the program to use it and not give an error (since the information is below, it wouldnt work without this)
//dont forget the semi-colon!
void meow2(int n);


int main(void) // most conventional to leave main function the more above the better
{
    int i = 0; //most conventional to start the counter on 0
    while (i < 3)
    {
        printf("meow with while loop\n");
        i++;
    }

    for (int b = 0; b < 3; b++) //first the counter, then the boolean, and then the action
    {
        printf("meow with for loop\n");
    }

    for (int a = 0; a < 3; a++)
    {
        meow();
    }

    {
        meow2(3);
    }
}

void meow(void)
{
    printf("meow with meow()\n");
}

void meow2(int n)
{
    for (int i=0; i<n; i++)
    {
        printf("meow with meow2()\n");
    }
}

