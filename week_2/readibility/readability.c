#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int read_test(string text);

int main(void)
{
    string text = get_string("Text: ");

    int grade = read_test(text);
    if (grade < 1)
        printf("Before Grade 1\n");
    else if (grade > 16)
        printf("Grade 16+\n");
    else
        printf("Grade %i\n", grade);
}

int read_test(string text)
{
    int number_letters = 0;
    int n = strlen(text);
    for (int i = 0; i < n; i++)
        if (isalpha(text[i]) && text[i] != 0)
        {
            number_letters += 1;
        }

    int number_spaces = 0;
    for (int x = 0; x < n; x++)
        if (text[x] == 32)
        {
            number_spaces += 1;
        }

    int number_words = number_spaces + 1;

    float average_letters = ((float) number_letters / (float) number_words) * 100;

    int number_sentences = 0;
    for (int a = 0; a < n; a++)
        if (text[a] == 46 || text[a] == 63 || text[a] == 33)
        {
            number_sentences += 1;
        }

    float average_sentences = ((float) number_sentences / (float) number_words) * 100;

    float index = ((0.0588 * average_letters) - (0.296 * average_sentences)) - 15.8;

    int rounded_index = (int) round(index);

    return rounded_index;
}
