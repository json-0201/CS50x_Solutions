#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


// Plaintext alphabet array (A-Z)
string NORMAL = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";


// program main body
int main(int argc, string argv[])
{

    // check for single command line argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // check for 26 character key
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // check for alphabetic character input
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
    }

    // check for duplicate character input
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        for (int j = i + 1; j < strlen(argv[1]); j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Key must contain each letter exactly once.\n");
                return 1;
            }
        }
    }
    // prompt user input for plaintext
    string plaintext = get_string("plaintext: ");

    // switch input plaintext to ciphertext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int pointer;

        // check for alphabetic character
        if (isalpha(plaintext[i]))
        {

            // if lowercase, switch and convert to lowercase in the end
            if (islower(plaintext[i]))
            {
                for (int j = 0; j < strlen(NORMAL); j++)
                {
                    if (NORMAL[j] == toupper(plaintext[i]))
                    {
                        pointer = j;
                    }
                }
                plaintext[i] = argv[1][pointer];
                plaintext[i] = tolower(plaintext[i]);
            }

            // if uppercase, switch and convert to uppercase in the end
            if (isupper(plaintext[i]))
            {
                for (int j = 0; j < strlen(NORMAL); j++)
                {
                    if (NORMAL[j] == toupper(plaintext[i]))
                    {
                        pointer = j;
                    }
                }
                plaintext[i] = argv[1][pointer];
                plaintext[i] = toupper(plaintext[i]);
            }
        }
    }
    string ciphertext = plaintext;
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}