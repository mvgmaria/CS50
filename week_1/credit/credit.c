#include <cs50.h>
#include <stdio.h>

const int MAX_DIGITS = 16;

void calculate_credit(long credit_card_number);

int main(void)
{
    long n;
    do
    {
        n = get_long("Please input your credit card number: ");
    }
    while (n < 0);

    calculate_credit(n);
}

void calculate_credit(long credit_card_number)
{
    int digits[MAX_DIGITS]; // An array that holds 16 elements (max_digits here specifies the lenght
                            // of the array, and later it will serve as the index)
    int length =
        0; // This variable will be put in the place of the mentioned index to indicate where to add
           // the processed numbers to the array. It starts as 0, as to append the first number to
           // the array and keeps incrementing with each pass of the loop

    // extracting logic
    while (credit_card_number > 0)
    {
        digits[length] = credit_card_number % 10;
        credit_card_number /= 10;
        length++;
    }

    // we initialize the variable sum at 0
    int sum = 0;

    // for loop so that as long as the index i is less than the length of the array, it will keep
    // looking for the 1,3,5,7 (I+=2) and so on position in the array, and then executing the
    // following operation it accounts for the cases where the product is formed by more than one
    // digit, in which case it separates the product and sums it (e.g. 18 ends up as 9) and finally
    // it sums the products in the sum variable that we started earlier
    for (int i = 1; i < length; i += 2)
    {
        int double_digit = digits[i] * 2;
        if (double_digit > 9)
        {
            double_digit = (double_digit / 10) + (double_digit % 10); // Sum the digits
        }
        sum += double_digit;
    }

    // now we have to get the numbers with an odd index and also add them to the previous sum
    for (int i = 0; i < length; i += 2)
    {
        sum += digits[i];
    }

    // final validation, so that if the sum ends in a 0 it keeps checking for the type of card, and
    // if not, it prints invalid
    if (sum % 10 == 0)
    {
        // add the conditions needed to check the card type, only if the number is valid (baased on
        // the length of the credit card number and in the number with which it starts) here length
        // is still the number of digits of the cards, since it served as the index before when
        // processing the credit_card_number into an array, and still holds that number
        if (length == 15 && digits[length - 1] == 3 &&
            (digits[length - 2] == 4 || digits[length - 2] == 7))
        {
            printf("AMEX\n");
        }
        else if (length == 16 && digits[length - 1] == 5 &&
                 (digits[length - 2] >= 1 && digits[length - 2] <= 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 13 || length == 16) && digits[length - 1] == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
