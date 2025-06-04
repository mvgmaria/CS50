#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(void)
{
    FILE *file = fopen("phonebook.csv", "a"); // a for append instead of write, so the program adds to the phonebook instead of overwriting

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s,%s\n", name, number);

    fclose(file);
}
