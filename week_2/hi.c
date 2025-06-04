#include <cs50.h>
#include <stdio.h>

int main (void)
{
    string s = "HI!";
    string t = "BYE!";
    printf("%s\n", s);
    printf("%s\n", t); // could be treated as an array of characters ("%c%c%c, s[0], s[1], s[2]); %c is the placeholder for "char" (as in character) type, which holds one byte of information, so one letter.
    // Also we could treat a string as an array of strings, instead of char, hence: string words[2]; words [0] = "HI!"; words [1] = "BYE!"; then we have the char level as: words [0][0] = "H"; words [0][1] = "i";
}
