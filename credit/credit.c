#include <cs50.h>
#include <stdio.h>

// call functions
long card_number(void);
bool is_valid(long number);

// main program
int main(void)
{
    // input card number
    long number = card_number();

    // calculate checksum, return boolean (T/F)
    bool valid = is_valid(number);

    // AMEX - begin with 34 or 37 - 15 digits
    if ((valid && (number % 1000000000000000) / 100000000000000 == 3) && ((number % 100000000000000) / 10000000000000 == 4
            || (number % 100000000000000) / 10000000000000 == 7))
    {
        printf("AMEX\n");
    }

    // MASTERCARD - begin with 51, 52, 53, 54, 55 - 16 digits
    else if ((valid && (number % 10000000000000000) / 1000000000000000 == 5) && ((number % 1000000000000000) / 100000000000000 == 1
             || (number % 1000000000000000) / 100000000000000 == 2 || (number % 1000000000000000) / 100000000000000 == 3
             || (number % 1000000000000000) / 100000000000000 == 4 || (number % 1000000000000000) / 100000000000000 == 5))
    {
        printf("MASTERCARD\n");
    }

    // VISA - begin with 4 - 13/16 digits
    else if (valid && ((((number % 10000000000000) / 1000000000000) == 4 && ((number % 100000000000000) / 10000000000000) == 0)
                       || ((number % 10000000000000000) / 1000000000000000) == 4))
    {
        printf("VISA\n");
    }

    // INVALID - None
    else
    {
        printf("INVALID\n");
    }
}

// input user card number
long card_number(void)
{
    long number = get_long("Number: ");
    return number;
}

// checksum function
bool is_valid(long number)
{
    long mod1 = 100; // second to the last digit
    long div1 = 10;

    long mod2 = 10; // last digit
    long div2 = 1;

    long digit1;
    int digit1_1; // first digit after *2
    int digit1_2; // second digit after *2

    long digit2;

    int ind = 0; // initialize index
    int sum = 0; // initialize sum



    while (ind < 8) // 8 iteration max for all types of card
    {
        digit1 = number % mod1;
        digit1 /= div1;
        digit1 *= 2;
        digit1_1 = digit1 % 10;
        digit1_2 = digit1 / 10;

        digit2 = number % mod2;
        digit2 /= div2;

        sum += digit1_1 + digit1_2 + digit2;
        // printf("sum: %i\n", sum);

        // move digit cursor for each new iteration
        mod1 *= 100;
        div1 *= 100;
        mod2 *= 100;
        div2 *= 100;

        ind ++;
    }

    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}