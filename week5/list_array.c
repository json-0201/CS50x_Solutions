#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // Dynamic allocation of an array of size 3
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }

    // Assign values to the array
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;

    // Time passes, want to add 4th elemenet
    // Dynamic RE-allocation of a new array of size 4
    int *tmp = realloc(list, 4 * sizeof(int));
    if (tmp == NULL)
    {
        free(list); // Free memory before exiting main loop
        return 1;
    }

    // Add fourth number to new array
    tmp[3] = 4;

    list = tmp; // No need to free "tmp" because it is written over "list", pointing to same values

    // Print new array and address for each element
    for (int i = 0; i< 4; i++)
    {
        printf("list[i]: %i\n", list[i]);
        printf("list[i] address: %p\n", &list[i]);
        printf("\n");
    }
    free(list); // Free the dynamically allocated heap memory after using
    return 0;

}