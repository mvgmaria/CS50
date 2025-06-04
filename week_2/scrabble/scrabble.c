#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int points[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int scrabble(string word);

int main(void)
{

    string player_1 = get_string("Player 1: ");
    string player_2 = get_string("Player 2: ");

    int score_1 = scrabble(player_1);
    int score_2 = scrabble(player_2);

    if (score_1 > score_2)
        printf("Player 1 wins\n");
    else if (score_2 > score_1)
        printf("Player 2 wins\n");
    else if (score_1 == score_2)
        printf("It's a tie\n");
}

int scrabble(string word)
{

    int score = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // following the ASCII codes, if A equals to 65, and we subtract 65 to that, we are getting
        // 0, and then we are getting the 0th position in the array of points, that follows the
        // order of the alphabet. Same goes for lowercase letters
        if (isupper(word[i]))
        {
            score += points[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += points[word[i] - 'a'];
        }
    }
    return score;
}
