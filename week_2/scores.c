#include <cs50.h>
#include <stdio.h>

int main(void)
{
    const int N = 3; // is common place to capitalize when we the variable is a constant (if we intend to change, its better to put it outside the int main function, in the global scope)
    int scores[N];
    for (int i = 0; i < N; i ++)
    {
        scores[i] = get_int("Score: ");
    }

printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / (float) N); // with (float) we convert the int n to a float type so that when we do the division it returns a float value even if the scores are integers
}
