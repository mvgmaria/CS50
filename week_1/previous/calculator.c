#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int("x: ");
    int y = get_int("y: ");

    float z = (float) x / (float) y; // typecasting those variables as float
    printf("0.20%f\n", z); // this placeholder is expecting an integer ("i") or a float ("f), of which we can determine the number of decimals ("0.5f")
}
