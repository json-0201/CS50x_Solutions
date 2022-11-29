#include <stdio.h>

// Function prototype
int fact(int n);

int main(void)
{
    int number, result;

    printf("Enter a number: ");
    // Input -> variable: number
    scanf("%d", &number);

    result = fact(number);
    printf("Factorial of %d is: %d\n", number, result);
}

int fact(int n)
{
    // Base case -> factorial 1 = 1
    if (n <= 1)
    {
        return n;
    }

    // Recursive case -> factorial(n) = n * factorial(n - 1)
    return n * fact(n - 1);
}