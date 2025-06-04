#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    // string names[] = {"Carter", "David", "John"};
    // string numbers[] = {"+1-123", "+1-234", "+1-345"}; //even if it seems counter-intuitive, its better to store the numbers as strings, because we are not going to make mathematical operations with them (also, we are including pluses and slashes in them)

    person people[3];

    people[0].name = "Carter"; // by typing the "." we access the atribute of choice
    people[0].number = "+1-123";
    

    string name = get_string("Name: ");
    for (int i = 0; i < 7; i++)
    {
        if (strcmp(people[i], name) == 0)
        {
            printf("Found %s\n", numbers[i]);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
