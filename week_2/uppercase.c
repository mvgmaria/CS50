#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
    string s = get_string("Before: ");
    printf("After: ");
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (s[i] >= 'a' && s[i] <= 'z') // this works because in ASCII these characters are together forming sort of a range, so we can use that to identify the upper and lower cases characters (we could also by number, and by subtracting or adding)
        {
            printf("%c", toupper(s[i]));
        }
        else
        {
        printf("%c", s[i]);
        }
    }
    printf("\n");
}
