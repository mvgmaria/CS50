#include <cs50.h>
#include <stdio.h>
//include <string.h> that has the function strlen to gauge the length of the string

int string_length(string s);

int main (void)
{
    string name = get_string("Name: ");
    int length = string_length(name);
    printf("%i\n", length);
}

int string_length(string s)
{
    int n = 0;
    while (s[n] != '\0') //meaning, since a string is an array of char and the last char is a 0 indicating the end of said array, as long as the string haas characters different than 0 (so we are iterating through it) the loop will keep running
    {
        n++;
    }
    return n;
}
