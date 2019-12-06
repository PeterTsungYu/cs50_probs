#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
// No matter the count of the candidates.
// The size of the array is defined by the max number.
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    int counter = 0;
    // Iterate over the names in the array of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // If the voted name is the matched the candidate's name,
        // increase the vote of the candidate and return true
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            counter = 1;
        }
        // If it is mismatched,
        // do nothing to the vote number
    }

    if (counter == 1)
        return true;
    else
        return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Create a new array to store the sorted struct
    candidate sorted[MAX];

    // a new array for a copy from the state array of candidates
    candidate ballots[MAX];

    // a tie counter
    int tie = 0;

    // Insertion sort the array of candidates into the just-named sorted array
    // Or, one could copy the whole array to a new array
    for (int i = 0; i < MAX; i++)
    {
        ballots[i] = candidates[i];
    }

    // The sorted is in the descendent order. (from the greater to the smaller)
    // First iteration goes through the array of candidates,
    // from the beginning till the end
    for (int q = 0; q < MAX; q++)
    {
        // Second iteration goes through the array of the array of the sorted,
        // from the beginning till the same position as the first iteration
        for(int v = 0, temp; v < (q+1); v++)
        {
            // When the one in the copy is greater than the one in the sorted,
            // swap them with a temporary container, temp
            // That is placing the greater into the sorted array and the smaller into the copy array
            // In the visualizing way, this is a simple way to make a space to insert the target and shift the others backward
            if (ballots[q].votes >= sorted[v].votes)
            {
                temp = sorted[v].votes;
                sorted[v].votes = ballots[q].votes;
                ballots[q].votes = temp;
            }
        }
    }

    // Count and print the ties with the greatest votes
    for (int i = 0; i < MAX; i++)
    {
        if (sorted[i].votes == sorted[0].votes)
        {
            printf("%s ", sorted[i].name);
        }
    }
    printf("\n");
    return;
}