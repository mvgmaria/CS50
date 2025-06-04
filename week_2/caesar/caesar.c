#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cipher_function(string text, int key);

int main(int argc, char *argv[])
{
    // in case of more than one argv
    if (argc != 2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }

    // in case of one argument but not integer (it checks for any special simbols, including a
    // minus)
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Please input a non negative integer");
            return 1;
        }
    }

    // convert the key to an integer (since it is a char/string type, because is the only type that
    // command line arguments can be passed as)
    int key = atoi(argv[1]);

    string plaintext = get_string("Plaintext:  ");

    // Call the cipher function
    cipher_function(plaintext, key);

    return 0;
}

void cipher_function(string text, int key)
{
    printf("Ciphertext: ");
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        char c = text[i];

        // if the char is alphabetic
        if (isalpha(c))
        {
            if (islower(c))
            {
                int output = (c - 'a' + key) % 26 + 'a';
                printf("%c", output);
            }
            else if (isupper(c))
            {
                int output = (c - 'A' + key) % 26 + 'A';
                printf("%c", output);
            }
        }

        else
        {
            // if its not alphabetic
            printf("%c", c);
        }
    }
    printf("\n");
}
