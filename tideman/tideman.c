#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool is_cycle(int tail, int head);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }

            // Test print ranks array (output: candidate index)
            // printf("ranks[%i]: %i\n", j, ranks[j]);
        }

        record_preferences(ranks);

        printf("\n");
    }

    // Test print preferences array
    /* for (int i = 0; i < candidate_count; i++)
    {
        for (int j =0; j < candidate_count; j++)
        {
            printf("preference[%i][%i]: %i\n", i, j, preferences[i][j]);
        }
    } */

    add_pairs();

    // Test print pairs array
    /* for (int i = 0; i < candidate_count * (candidate_count - 1) / 2; i++)
    {
        printf("pairs[%i] winner's index = %i\n", i, pairs[i].winner);
        printf("pairs[%i] loser's index = %i\n", i, pairs[i].loser);
    } */

    // Print variable "pair_count"
    // printf("pair count: %i\n", pair_count);

    sort_pairs();

    // Test print sorted pairs array
    /* for (int i = 0; i < pair_count; i++)
    {
        printf("sorted pairs[%i] winner's index = %i\n", i, pairs[i].winner);
        printf("sorted pairs[%i] loser's index = %i\n", i, pairs[i].loser);
    } */

    lock_pairs();

    // Test print locked array
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("locked[%i][%i] = %d\n", i, j, locked[i][j]);
        }
    }

    print_winner();

    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Initialize count for name detection (return false if not detected)
    int count = 0;

    // Update ranks array (ranks[i] is the "i"th preference of the candidate index "i")
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            count++;
        }
    }
    if (count == 0)
    {
        return false;
    }

    return true;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop through adjacent comparison, (i < j)
    // Increment preferences[ranks[i]][ranks[j]]
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop through preferences, compare indices, append pairs array attributes
    // Initialize pairs array index number
    int num = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[num].winner = i;
                pairs[num].loser = j;
                pair_count++;
            }
            if (preferences[j][i] > preferences[i][j])
            {
                pairs[num].winner = j;
                pairs[num].loser = i;
                pair_count++;
            }
            num++;
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Initialize strength victory array for each pair count
    int strength_victory[pair_count];

    // Initialize temporary pair struct
    pair temp;

    // Loop through all pairs and append stength of victory
    for (int k = 0; k < pair_count; k++)
    {
        strength_victory[k] = preferences[pairs[k].winner][pairs[k].loser];
    }

    // Nest loop through i and j = i+1 and sort
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (strength_victory[i] < strength_victory[j])
            {
                temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }

    return;
}

// Return true if cycle is detected
// Recursive function
bool is_cycle(int tail, int head)
{
    // Base case -> cycle detected, return true
    if (tail == head)
    {
        return true;
    }

    // Recursive case -> check for every candidate which loser wins over
    // ex) A ->B: does B points to any other candidate?
    for (int i = 0; i < candidate_count; i++)
    {
        // if loser does win over other candidate, start the recursive process to check for cycle
        if (locked[tail][i])
        {
            // New tail is the original loser's loser / head does not change
            if (is_cycle(i, head))
            {
                // Recursively check cycle until tail and head meet
                return true;
            }
        }
    }

    // if loser does not win over any other candidate, lock the pair by returning false
    return false;

}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop through pairs array
    for (int i = 0; i < pair_count; i++)
    {
        // If cycle not detected (is_cycle == false)
        if (!is_cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Create winner index variable
    int winner_index;

    // Increment counter if arrow is pointed to candidates[i]
    for (int i = 0; i < candidate_count; i++)
    {
        int count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                count++;
            }
        }
        // printf("candidate[%i]'s count = %i\n", i, count);

        // Set winner index if candidates[i]'s count is 0
        if (count == 0)
        {
            winner_index = i;
        }
    }

    // Print out the winner of election
    printf("%s\n", candidates[winner_index]);

    return;
}