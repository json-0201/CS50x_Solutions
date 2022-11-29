// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1]; // +1 for zero-byte
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Initialize variable for word count
unsigned long wc = 0;

// Hash table, an N-size array of pointers
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Get hash value
    unsigned int hash_number = hash(word);

    // Initialize cursor
    node *cursor = table[hash_number];

    // Loop through the linked list
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }

        // Move to next node
        cursor = cursor -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read strings from file one at a time
    char vocabulary[LENGTH + 1]; // buffer
    unsigned int hash_number;

    // Read each vocabulary until the end
    while (fscanf(file, "%s", vocabulary) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        // Copy current word to new node
        strcpy(n -> word, vocabulary);

        // Hash number from hash function
        hash_number = hash(vocabulary);

        // Check if head of linked list is NULL
        if (table[hash_number] == NULL)
        {
            n -> next = NULL;
        }

        else
        {
            // Point current node pointer to the first element of linked list
            n -> next = table[hash_number];
        }

        // Point the header to current node
        table[hash_number] = n;

        // Increment word count
        wc++;
    }

    fclose(file);

    // Dictionary loaded
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // Return word count from load function
    if (wc > 0)
    {
        return wc;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For each bucket of hash table
    for (int i = 0; i < N; i++)
    {
        // Set cursor to the beginning of the linked list
        node *cursor = table[i];

        // If cursor not NULL, free memory using "tmp"
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
}