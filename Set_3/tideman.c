#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Invalid vote counted as a denoted integer
#define INVALID (MAX+1)

int pair_count;
int candidate_count;

// global int default value is 0
// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// global boolean default value is false
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

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
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
                // if it is a invalid vote, the main would return 3 and the program is ended.
                // return 3;
                // or there is an option for the invalid vote and keep the program continue its work.(INVALID 10)
            }
        }
        record_preferences(ranks);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    bool counter = false;
    // To match a name between fun_arg:name and the array of candidates.
    // Iteration through the array of candidates to match a voted name.
    // If matched, put the index of the candidates into the array of ranks, and set counter be true.
    for (int i = 0; i < candidate_count; i++)
    // Iterate through the whole array of candidates.
    // i is the index of the array of candidates
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            counter = true;
            // To check if there is a double voted name from a ballot.
            // If the index of the candidate is already inside the array of rank,
            // return as an invalid vote by denoted the index of candidates as INVALID 10
            // and setting counter be false.
            for (int v = 0; v < (rank - 1); v++)
            // Iterate through the array of ranks till the one before the current rank.
            // v is the index of the array of ranks
            {
                if (i == ranks[v])
                {
                    ranks[rank] = INVALID;
                    counter = false;
                }
            }
        }
    }
    // Return the counter as a valid or invalid vote.
    return counter;
}

// Update 2-D preferences when given one voter's ranks
void record_preferences(int ranks[])
{
    // The preferences represent the number of voters who prefer candidate i over candidate j.
    // Mapping the index of the candidates in the value of ranks to the array of preferences.
    for (int i = 0; i < (candidate_count - 1); i++)
    // Iterate through each ranks from first to the one before the last as a preferred candidate i over candidate v.
    {
        for (int v = (i + 1); v < candidate_count; v++)
        // Iterate through each ranks from the next index (to except i itself) of the current index of ranks to the last one in the ranks as a candidate v.
        {
            // if the ranks[i] is INVALID, then no need to record into the array of preferences. Thus, continue to the next i.
            if (ranks[i] == INVALID)
                break;
            preferences[ranks[i]][ranks[v]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // temps array for debugging
    pair temps[candidate_count * (candidate_count - 1) / 2];

    // Iterate through the 2-D array of preferences.
    // Except itself and except the swap sequence (ex. (0,1) == (1,0)).
    for (int i = 0; i < candidate_count; i++)
    {
        for (int v = (i + 1); v < candidate_count; v++)
        {
            if (preferences[i][v] > preferences[v][i])
            {
                temps[pair_count].winner = i;
                temps[pair_count].loser = v;
            }
            // Due to there is no way for the preferences[v][i] would be iterated through during this double iteration,
            // thus it should be an explicit condition here.
            else if (preferences[i][v] < preferences[v][i])
            {
                temps[pair_count].winner = v;
                temps[pair_count].loser = i;
            }
            // If it is a tie, no need to count into the global array of pairs.
            // And, no need to count as an increment of global integer of pair_count. Thus, continue to the next v.
            else
                continue;
            pair_count++;
        }
    }

    // Update the array of pairs
    for (int u = 0; u < pair_count; u++)
    {
        pairs[u] = temps[u];
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// In order to do the recursion, the fun_arg cannot be void.
void mergeSort(int len)
{
    // Merge sort through the array of pairs
    // Base case: Stop when len of the portion array is equal to 1.
    if (len <= 1)
        return;

    // Recursive case: Each step is gonna make a portion half.
    // Each half (right and left) is sorted in the last step.
    // Thus, the "Sort left" and "Sort right" are hiden in the recursion "Merge"

    // But, if len = 3, then 3/2 return 1...
    //TODO, if len is odd...
    //TODO, if len is even...
    mergeSort(len / 2);

    // Plus one additional element: Merge section.
    // Iteration is gonna divided the whole array into smaller portions in each recursive step.
    // v is defined as a step indicator.
    // len is a multiplication factor.
    for (int v = 0; v < (pair_count / len); v++)
    // Ex. if the len = 2, and the whole array size is 8. Then 8/2 = 4 is going to be the number of the iteraton.
    {
        // Define the left margin and the right margin first
        int left = len * v;
        int right = len * (v + 1 / 2);

        // Define a array of temp in the size one len
        // To put the sorted array into the array of temp.
        pair temp[len];

        // Merge by comparing each time the greatest number of both halves
        // The position/index of the sorted temp is defined by i.
        for (int i = 0; i < len; i++)
        // The iteration is going throgh from each position to a len away of the position.
        // Ex. the position is now at 2(len)*1(v) = 2. It will end at 2*(1+1) = 4, which is a len away the initial position for each iteration.
        {
            // If the greatest in right half is greater or equal than the greatest in the left half,
            // The right one will be copied to the array of temp, which is meant to be a sorted array.
            // Since the invalid vote is an option, the func: lock_pairs should use the difference to measure the edge
            // Ex. edge == preferences[winner][loser] - preferences[pairs[loser][winner].
            if ((preferences[pairs[left].winner][pairs[left].loser] - preferences[pairs[left].loser][pairs[left].winner])
                <= (preferences[pairs[right].winner][pairs[right].loser] - preferences[pairs[right].loser][pairs[right].winner]))
            {
                temp[i] = pairs[right];
                right++;
            }
            // If the greatest in left half is greater than the greatest in the right half,
            // The left one will be copied to the array of temp, which is meant to be a sorted array.
            else
            {
                temp[i] = pairs[left];
                left++;
            }
        }

        // Array of temp overrides the original array of pairs
        for (int u = 0; u < len; u++)
        {
            pairs[(v * len) + u] = temp[u];
        }
    }
    return;
}

void sort_pairs(void)
{
    mergeSort(pair_count);
}

// Lock pairs (a 2-D boolean array. “adjacency matrix”) into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // For every items, setting the pairs source default as true when mapping pairs to locked.
        locked[pairs[i].winner][pairs[i].loser] = true;
    }

    // A circle is composed of three people => Three iteration loops.
    for (int i = 0; i < pair_count; i++)
    // It is important to iterate every element in the array of pairs.
    // Since the composition of the a circle would be different arrangement.
    // Ex. If (A,B,C) is examined, it doesn't mean (B > C) will be a locked edge.
    // Cuz (B,C,D) might override the default values. And say, hey, (B > C) is an exception.
    {
        // (All - Exception), the only exception will be (A > B > C > A).
        // If the value is already fault, then remains it.
        // Otherwise, go into the followings conditions.
        if (locked[pairs[i].winner][pairs[i].loser] != false)
            for (int v = (i + 1); v < pair_count; v++)
                if (pairs[i].loser == pairs[v].winner)
                    for (int u = (v + 1); u < pair_count; u++)
                        // If (A > B > C > A), then set the true to the false.
                        if ((pairs[v].loser == pairs[u].winner) && (pairs[u].loser == pairs[i].winner))
                            locked[pairs[u].winner][pairs[u].loser] = false;
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Define a array of counter for counting the source
    // (ex. source == A > B. and it is the true in the array of locked)
    int counter[candidate_count];

    // Define a temp value for a memory container for searching the highest counter
    int temp = 0;
    // Define a temp value for a memory container for searching the index of candidates with the highest counter
    int winner = 0;

    // Iterate through the 2-D array of locked looking for the true value.
    for (int i = 0; i < candidate_count; i ++)
    {
        // Set the counter array values to 0
        counter[i] = 0;
        for (int u = 0; u < candidate_count; u++)
        {
            // Except itself
            if (i == u)
                continue;
            // source = #true - #false
            if (locked[i][u] == true)
                counter[i]++;
            else
                counter[i]--;
        }
    }

    // Iterate through the array of counter, and search for the highest counter.
    for (int i = 0; i < candidate_count; i++)
    {
        if (counter[i] > temp)
        {
            temp = counter[i];
            winner = i;
        }
    }

    // If there are tie winners, print them all.
    for (int i = 0; i < candidate_count; i++)
    {
        if (counter[i] == temp)
        {
            printf("%s", candidates[i]);
        }
    }
    printf("\n");
    return;
}