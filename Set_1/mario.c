#include <cs50.h>
#include <stdio.h>

void pyramid(int);

int main(void)
{
    int n;
    do 
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    pyramid(n);
} 

void space(int q)
{
    for (int v = 0; v < q; v++)
    {
        printf(" ");
    }
}

void hash(int q)
{
    for (int v = 0; v < q; v++)
    {
        printf("#");
    }
}

void pyramid(int n)
{
    for (int q = 0; q < n; q++) 
    {
        space(n - q - 1);
        hash(q + 1);
        printf("  ");
        hash(q + 1);
        printf("\n");
    }
}

