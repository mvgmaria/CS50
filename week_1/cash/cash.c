#include <cs50.h>
#include <stdio.h>

void calculate_change(int change);

int main(void)
{
    int n;
    do
    {
        n = get_int("Change owed: ");
    }
    while (n < 0);

    calculate_change(n);
}

void calculate_change(int change)
{
    int coin_25 = change / 25;
    int rest_change = change % 25;

    int coin_10 = rest_change / 10;
    rest_change %= 10;

    int coin_5 = rest_change / 5;
    rest_change %= 5;

    int coin_1 = rest_change;

    int total_coins = coin_25 + coin_10 + coin_5 + coin_1;

    printf("Total coins: %d\n", total_coins);
}

