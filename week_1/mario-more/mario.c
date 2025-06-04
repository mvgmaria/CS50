
#include <cs50.h>
#include <stdio.h>

void print_row(int bricks);
void print_spaces(int spaces);

int main(void)
{
    int n;
    do // a type of loop that can be reused, it has to be used with the while statement below
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        print_spaces(n - i - 1);
        print_row(i + 1);
        printf("  ");
        print_row(i + 1);
        printf("\n");
    }
}

void print_row(int bricks)
{
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
}

void print_spaces(int spaces)
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
}
