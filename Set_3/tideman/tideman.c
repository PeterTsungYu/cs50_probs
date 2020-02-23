#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

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
        for (int rank = 0; rank < candidate_count; rank++)
        {
            string name = get_string("Rank %i: ", rank + 1);

            if (!vote(rank, name, ranks))
            {
                printf("Invalid vote.\n");
                // if it is an invalid vote, the main would return 3 and the program is ended.
                return 3;
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
            preferences[ranks[i]][ranks[v]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Iterate through the 2-D array of preferences.
    // Except itself and except the swap sequence (ex. (0,1) == (1,0)).
    for (int i = 0; i < candidate_count; i++)
    {
        for (int v = (i + 1); v < candidate_count; v++)
        {
            // If it is a tie, no need to count into the global array of pairs.
            // And, no need to count as an increment of global integer of pair_count. Thus, continue to the next v.
            if (preferences[i][v] == preferences[v][i])
                continue;

            // Due to there is no way for the preferences[v][i] would be iterated through during this double iteration, ((0,1) == (1,0))
            // thus it should be an explicit condition here.
            else if (preferences[i][v] > preferences[v][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = v;
            }

            else
            {
                pairs[pair_count].winner = v;
                pairs[pair_count].loser = i;
            }
            pair_count++;
        }
    }
    return;
}

void sort_pairs(void)
{
    // Bubble sort to sort the global var: pairs, in the descendant order
    int swap = 1;
    int len = pair_count;

    while (swap != 0)
    {
        swap = 0;
        for (int i = 1; i < len; i++)
        {
            pair temp;
            if (preferences[pairs[i].winner][pairs[i].loser] >= preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {
                temp = pairs[i];
                pairs[i] = pairs[i - 1];
                pairs[i - 1] = temp;
                swap++;
            }
        }
        len--;
    }
}

// Lock pairs (a 2-D boolean array. “adjacency matrix”) into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // initialize an array to record the index: i if cycle is matched
    // Set to zero
    int cycArr[(int)round(pair_count / 3)];
    for (int y = 0; y < round(pair_count / 3); y++)
    {
        cycArr[y] = 0;
    }
    int cycInd = 0;

    // A cycle is formed by three pairs with three candidates
    // Thus, a cycle needs three loops to validate
    // First for-loop to iterate through the array: pairs. This is the first pair.
    // Iteration from beginning to the end, no exception
    for (int i = 0; i < pair_count; i++)
    {
        // Mark a boolean value if a cycle condition is matched
        bool cycle = false;

        // Second for-loop to trace back
        // Additional exception: if cycle is matched, break the loop
        for (int u = 0; (u < i) && (cycle == false); u++)
        {
            // A mark to avoid the iteration to rerun the cycle pairs in the current loop
            bool u_rerun = 0;
            for (int w = 0; w < cycInd; w++)
            {
                if (u == cycArr[w])
                {
                    u_rerun = 1;
                    break;
                }
            }
            if (u_rerun == 1)
            {
                continue;
            }

            // if find the second pair, then the third loop will be initialized
            // This is the first case for the second loop
            if (pairs[i].loser == pairs[u].winner)
            {
                // Third for-loop to trace back
                // Additional exceptions: if cycle is matched, break the loop
                for (int v = 0; v < i; v++)
                {
                    // A mark to avoid the iteration to rerun the cycle pairs in the current loop
                    bool v_rerun = 0;
                    for (int w = 0; w < cycInd; w++)
                    {
                        if (v == cycArr[w])
                        {
                            v_rerun = 1;
                            break;
                        }
                    }
                    if (v_rerun == 1)
                    {
                        continue;
                    }

                    // Exception: avoid the double check between the second and the third loops
                    if (v != u)
                    {
                        // if find the third pair, then the cycle (first pair: pairs[i]) is marked
                        if ((pairs[u].loser == pairs[v].winner) && (pairs[v].loser == pairs[i].winner))
                        {
                            cycle = true;
                            cycArr[cycInd] = i;
                            cycInd++;
                            break;
                        }
                    }
                }
            }

            // if find the second pair, then the third loop will be initialized
            // This is the second case for the second loop
            if (pairs[i].winner == pairs[u].loser)
            {
                for (int v = 0;  v < i; v++)
                {
                    bool v_rerun = 0;

                    for (int w = 0; w < cycInd; w++)
                    {
                        if (v == cycArr[w])
                        {
                            v_rerun = 1;
                            break;
                        }
                    }
                    if (v_rerun == 1)
                    {
                        continue;
                    }
                    if (v != u)
                    {
                        if ((pairs[u].winner == pairs[v].loser) && (pairs[v].winner == pairs[i].loser))
                        {
                            cycle = true;
                            cycArr[cycInd] = i;
                            cycInd++;
                            break;
                        }
                    }
                }
            }
        }

        // lock it into the array: locked if it is not a cycle
        if (cycle == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
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
            printf("%s", candidates[i]);
    }
    printf("\n");
    return;
}