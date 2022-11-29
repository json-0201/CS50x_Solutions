#include <stdio.h>

// Function prototype
int fib(int n);

int main(void)
{
    int number, result;

    printf("Enter a number: ");
    // Input -> variable: number
    scanf("%d", &number);

    result = fib(number);
    printf("Fibonacci of %d is: %d\n", number, result);
}

int fib(int n)
{
    // Base case -> fibonacci 1 = 0, 2 = 1
    if (n <= 2)
    {
        return 1;
    }

    // Recursive case -> fibonacci(n) = fibonacci(n - 1) + fibonacci(n - 2)
    return fib(n - 1) + fib(n - 2);
}