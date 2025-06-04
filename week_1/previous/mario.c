#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do // a type of loop that can be reused, it has to be used with the while statement below
        {
            n = get_int("Size: ");
        }
    while(n < 1);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}
