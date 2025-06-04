#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

void draw(int n);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);
}

void draw(int n)
{
    //If nothing to draw
    if (n <= 0)
    {
        return; // equal to 'quit'
    }
    // instead of nesting a loop inside the other as in the iteration.c program, we are calling the function again, but with a lesser n number each time, so it stops at a point, instead of running forever
    draw (n-1); // this resembles the for loop that keeps iterating until certain point

    for (int i = 0; i < n; i++)
    {
        printf("#");
    }
    printf("\n");
}

