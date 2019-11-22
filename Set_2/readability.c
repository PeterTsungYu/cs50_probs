#include <stdio.h>
#include <cs50.h>

int length(string s);
void count(string s, int arr[]);

int main(void)
{
    int counts[3];
    string text = get_string("Text: ");
    count(text, counts);
    float L = (float) counts[0] / counts[1] * 100;
    float S = (float) counts[2] / counts[1] * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    //printf("Length: %i\n", length(text));
    //printf("%i letter(s)\n%i word(s)\n%i sentence(s)\n", counts[0], counts[1], counts[2]);
    //printf("L: %f\nS: %f\n", L, S);
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}

int length(string s)
{
    int counter = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        counter++;
    }
    return counter;
}

void count(string s, int arr[])
{
    int letters = 0;
    int words = 0;
    int sentences = 0;
    for (int i = 0, n = length(s); i < n; i++)
    {
        if ((s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= 'a' && s[i] <= 'z'))
        {
            letters++;
            if ((s[i + 1] == 0) || (s[i + 1] == 33) || (s[i + 1] == 46) || (s[i + 1] == 63))
            {
                sentences++;
                words++;
            }
            else if ((s[i + 1] == 32) || (s[i + 1] == 34) || (s[i + 1] == 41) || (s[i + 1] == 44) || (s[i + 1] == 58) || (s[i + 1] == 59)
                     || (s[i + 1] == 93) || (s[i + 1] == 125))
            {
                words++;
            }
        }
    }
    arr[0] = letters;
    arr[1] = words;
    arr[2] = sentences;
}