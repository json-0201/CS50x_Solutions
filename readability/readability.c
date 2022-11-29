#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h> // for rounding


// Initialize count functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
string coleman_liau_index(int letters, int words, int sentences);


// Program main body
int main(void)
{
    string text = get_string("Text: ");
    printf("%s\n", text);

    int letters = count_letters(text);
    printf("%i letters\n", letters);

    int words = count_words(text);
    printf("%i words\n", words);

    int sentences = count_sentences(text);
    printf("%i sentences\n", sentences);

    string grade_level = coleman_liau_index(letters, words, sentences);
    printf("%s\n", grade_level);
}


// Count letters (count alphabetic character using "isalpha" - ctype.h)
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            letters ++;
        }
    }
    return letters;
}


// Counter words (number of words = number spaces + 1)
int count_words(string text)
{
    int spaces = 0;
    int words;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            spaces ++;
        }
    }

    words = spaces + 1;

    return words;
}


// Counter sentences (detect '.', '!', '?')
int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            sentences ++;
        }
    }
    return sentences;
}


// Calculate Coleman Liau Index
string coleman_liau_index(int letters, int words, int sentences)
{
    float lpw; // average number of letters per 100 words
    float spw; // average number of sentences per 100 words
    int index;
    char grade[8];
    string grade_level;

    lpw = (float) letters / (float) words * 100;
    spw = (float) sentences / (float) words * 100;

    index = round((0.0588 * lpw) - (0.296 * spw) - 15.8);


    if (index > 0 && index <= 15)
    {
        sprintf(grade, "Grade %i", index);
        grade_level = grade;
    }
    else if (index > 15)
    {
        grade_level = "Grade 16+";
    }
    else
    {
        grade_level = "Before Grade 1";
    }
    return grade_level;
}