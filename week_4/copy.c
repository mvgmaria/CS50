#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");

    // malloc function is meant to search for the space in memory of as many bytes as we write as the argument (dont forget the null character)
    char *t = malloc(strlen(s) + 1);

    // to account for the null character we code the loop to run until i is less OR equal to n (which would be one run more than a standard loop, since we are counting the 0), so now it would copy the next char after the 'last' one, which is the null
    for (int i = 0, n = strlen(s); i <= n; i++)
    {
        t[i] = s[i];
    }

    // this chunk could be subtitued with strcpy(x,y) - it will copy y into x

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }
    printf("%s\n", s);
    printf("%s\n", t);

    free(t); // when we stop using the memory called by malloc, we have to free it so the computer can access it for other means
    return 0;
}
