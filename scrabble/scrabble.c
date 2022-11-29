#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet (A-Z)
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// 1 pt - A E I L N O R S T U
// 2 pts - D G
// 3 pts - B C M P
// 4 pts - F H V W Y
// 5 pts - K
// 8 pts - J X
// 10 pts - Q Z

// let the compiler know function "compute_score" exists
int compute_score(string word);

// program main body
int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int index;
    int point;
    int sum = 0;
    for (index = 0; word[index] != '\0'; index++)
    {
        // make each character uppercase
        word[index] = toupper(word[index]);

        // Print ASCII values of each character
        // printf("%i\n", word[index]);

        // add points, using ASCII value of uppercase letter
        if (word[index] == 65 || word[index] == 69 || word[index] == 73 || word[index] == 76 || word[index] == 78 ||
            word[index] == 79 || word[index] == 82 || word[index] == 83 || word[index] == 84 || word[index] == 85)
        {
            point = 1;
            sum += point;
        }
        if (word[index] == 68 || word[index] == 71)
        {
            point = 2;
            sum += point;
        }
        if (word[index] == 66 || word[index] == 67 || word[index] == 77 || word[index] == 80)
        {
            point = 3;
            sum += point;
        }
        if (word[index] == 70 || word[index] == 72 || word[index] == 86 || word[index] == 87 || word[index] == 89)
        {
            point = 4;
            sum += point;
        }
        if (word[index] == 75)
        {
            point = 5;
            sum += point;
        }
        if (word[index] == 74 || word[index] == 88)
        {
            point = 8;
            sum += point;
        }
        if (word[index] == 81 || word[index] ==  90)
        {
            point = 10;
            sum += point;
        }
    }
    // printf("sum: %i\n", sum);
    return sum;
}