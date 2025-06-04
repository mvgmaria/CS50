#include <cs50.h>
#include <stdio.h>

const int N = 3;

float average(int length, int array[]);

int main(void)
{
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", average(N, scores)); // with (float) we convert the int n to a float type so that when we do the division it returns a float value even if the scores are integers
}

float average(int length, int array[])
{
    int sum = 0;
    for (int i = 0; i < length; i++)
    {
        sum += array[i]; // "acumulator way"
    }
    return sum / (float) length;
}
