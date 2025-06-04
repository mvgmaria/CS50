#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name_input = get_string("What's your name? ");
    printf("Hello, %s\n", name_input);
}
