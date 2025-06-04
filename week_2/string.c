#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    string s = get_string("Input: ");
    printf("Output: \n");
    for (int i = 0, n = strlen(s); i < n; i++) // this is to avoid looping through the string every time that we are getting a character, so we can create a variable in the same for loop, in its initialization part (instead of in the scope of the function, so above that line)
    // also, as we use the comma, the program assumes that n is also an int
    {
        printf("%c\n", s[i]);
    }
}
