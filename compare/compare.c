#include <stdio.h>
#include <cs50.h>
#include <string.h>


int main(void)
{
    char *str_1 = get_string("string1: ");
    char *str_2 = get_string("string2: ");

    printf("string1 address: %p\n", str_1);
    printf("string2 address: %p\n", str_2);

    int count = 0;

    for (int i = 0; i < strlen(str_1); i++)
    {
        printf("str_1[%i]: %p\n", i, &str_1[i]);
        printf("str_2[%i]: %p\n", i, &str_2[i]);
        if (*(str_1 + i) == *(str_2 + i))
        count++;
    }
    if (count == strlen(str_1) && count == strlen(str_2))
        printf("same!\n");
    else
        printf("different!\n");
}