#include <stdio.h>
#include <cs50.h>

int length(long n);
int checksum(long n);
int prefix(long n);
void valid(long n);

int main(void)
{
    long n;
    n = get_long("Your crdedit card number: \n");
    printf("%i\n", length(n));
    printf("%i\n", checksum(n));
    printf("%i\n", prefix(n));
    valid(n);
}

int length(long n)
{
    int digit = 0;
    if (n >= 10)
    {
        digit = 1;
    }
    do
    {
        digit ++;
        n = n / 10;
    }
    while (n >= 10);
    return digit;
}

int checksum(long n)
{
    int second;
    int first;
    int doubled;
    int sum = 0;
    do
    {
        second = 2 * (n % 100 - n % 10) / 10;
        if (second >= 10)
        {
            doubled = 1 + second % 10;
        }
        else 
        {
            doubled = second;
        }
        first = n % 10;
        sum = sum + first + doubled;
        n = (n - n % 100) / 100;
    }
    while (n > 0);
    return sum = sum % 10;
}

int prefix(long n)
{
    int prefix;
    if (length(n) == 15) 
    {
        return prefix = (n - n % 10000000000000) / 10000000000000;
    }
    else if (length(n) == 16) 
    {
        return prefix = (n - n % 100000000000000) / 100000000000000;
    }
    else if (length(n) == 13) 
    {
        return prefix = (n - n % 100000000000) / 100000000000;
    }
    else 
    {
        return n;
    }
}

void valid(long n)
{
    int predigit = prefix(n);
    if (checksum(n) == 0)
    {
        if (predigit == 34 || predigit == 37)
        {
            printf("AMEX\n");
        }
        if (predigit == 51 || predigit == 52 || predigit == 53 || predigit == 54 || predigit == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (((predigit - predigit % 10) / 10) == 4)
        {
            printf("VISA\n");
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else 
    {
        printf("INVALID\n");
    }
}