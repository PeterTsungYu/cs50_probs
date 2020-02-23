#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct
{
    int winner;
    int loser;
}
pair;

pair pairs[5];
int pair_count = 5;


int main(void)
{
    pairs[0].winner = 1;
    pairs[0].loser = 2;
    pairs[1].winner = 2;
    pairs[1].loser = 3;
    pairs[2].winner = 3;
    pairs[2].loser = 1;
    pairs[3].winner = 4;
    pairs[3].loser = 3;
    pairs[4].winner = 1;
    pairs[4].loser = 4;

    int cycArr[3];
    cycArr[0] = 0;
    cycArr[1] = 0;
    cycArr[2] = 0;
    int cycInd = 0;

    for (int i = 0; i < pair_count; i++)
    {
        bool cycle = 0;

        for (int u = 0; (u < i) && (cycle == 0); u++)
        {
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
            if (pairs[i].loser == pairs[u].winner)
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
                        if ((pairs[u].loser == pairs[v].winner) && (pairs[v].loser == pairs[i].winner))
                        {
                            cycle = 1;
                            cycArr[cycInd] = i;
                            cycInd++;
                            printf("%i, %i\n", pairs[i].winner, pairs[i].loser);
                            break;
                        }
                    }
                }
            }

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
                            cycle = 1;
                            cycArr[cycInd] = i;
                            cycInd++;
                            printf("%i, %i\n", pairs[i].winner, pairs[i].loser);
                            break;
                        }
                    }
                }
            }
        }
    }
    return 0;
}