#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void subs_function(string text, string key);

int main(int argc, char *argv[])
{
    string key = argv[1];
    // in case of more than one argv
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // in case of strings of less than 26 characters
    int n = strlen(key);
    if (n != 26)
    {
        printf("Please input a 26 character string");
        return 1;
    }

    // handling of special characters in the key
    for (int i = 0; i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Please input only alphabetic characters");
            return 1;
        }
    }

    // handling of repeated characters in the key
    int freq[26] = {0}; // Initialize frequency array to track letters

    for (int i = 0; i < 26; i++)
    {
        int index = tolower(key[i]) - 'a'; // Convert letter to lowercase and map it to an index
        freq[index]++;                     // Increment the frequency for that letter

        if (freq[index] > 1) // If any letter appears more than once
        {
            printf("Duplicate detected! Key contains repeated characters.\n");
            return 1; // Exit with an error
        }
    }

    string plaintext = get_string("Plaintext:  ");

    // Call the cipher function
    subs_function(plaintext, key);

    return 0;
}

void subs_function(string text, string key)
// iterate through the plain text and then through the key, and get the positions relative to 26 of
// each of them (based on their ascii values), then "match" them if its a symbol it hould print
// unmodified
{

    printf("ciphertext: ");
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        char c = text[i];

        // if the char is alphabetic
        if (isalpha(c))
        {
            if (islower(c))
            {
                int new_position = c - 'a';
                int new_char = key[new_position];
                if (islower(new_char))
                {
                    printf("%c", new_char);
                }
                else if (isupper(new_char))
                {
                    printf("%c", tolower(new_char));
                }
            }

            else if (isupper(c))
            {
                int new_position = c - 'A';
                int new_char = key[new_position];
                if (islower(new_char))
                {
                    printf("%c", toupper(new_char));
                }
                else if (isupper(new_char))
                {
                    printf("%c", new_char);
                }
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
