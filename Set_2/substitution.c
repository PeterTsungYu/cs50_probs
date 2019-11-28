#include <stdio.h>
#include <cs50.h>
#include <string.h>

//cases diff. between upper and lower
const int cases = 32;
const int keylen = 26;
const int totlen = (1 + keylen) * keylen / 2;

string substitute(string s, string k);
int length(string s);
bool alphabet(string s);;

int main(int argc, string argv[])
{
    //check the number of arguments
    if (argc == 2)
    {
        //check if the number of the key is valid
        if (length(argv[1]) == keylen)
        {
            //check if the key's letters are valid
            if (alphabet(argv[1]) == true)
            {
                string plain = get_string("plaintext: ");
                printf("ciphertext: %s\n", substitute(plain, argv[1]));
                return 0;
            }
            else
            {
                printf("Key must contain only letters of the alphabet and must not have duplicate letters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain %i characters.\n", keylen);
            return 1;
        }
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
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

bool alphabet(string s)
{
    int alphabool = 1;
    //check all the letters are the alphabets
    //check no duplicate letters
    for (int i = 0; alphabool == 1 && s[i] != '\0'; i++)
    {
        if ((s[i] < 65) || ((s[i] > 90) && (s[i] < 97)) || (s[i] > 122))
        {
            alphabool = 0;
        }
        for (int v = i + 1; alphabool == 1 && s[v] != '\0'; v++)
        {
            int mod = (s[i] - s[v]) % cases;
            if (mod == 0)
            {
                alphabool = 0;
            }
        }
    }
    return alphabool;
}

string substitute(string s, string k)
{
    int len = length(s);
    char ciphers[len];
    string ciphertext = "";
    for (int i = 0, index = 0; s[i] != '\0'; i++)
    {
        //Uppercase letters
        if ((s[i] >= 65) && (s[i] <= 90))
        {
            index = s[i] - cases * 2 - 1;
            //if the letter in the key is uppercase. Return the uppercase.
            if (k[index] <= 90)
            {
                ciphers[i] = k[index];
            }
            else
            {
                ciphers[i] = k[index] - cases;
            }
        }
        //Lowercase letters
        else if ((s[i] >= 97) && (s[i] <= 122))
        {
            index = s[i] - cases * 3 - 1;
            //if the letter in the key is lowercase. Return the lowercase.
            if (k[index] > 90)
            {
                ciphers[i] = k[index];
            }
            else
            {
                ciphers[i] = k[index] + cases;
            }
        }
        else
        {
            ciphers[i] = s[i];
        }
    }
    //a C-style string is essentially an array of characters with the special character null ('\0') at the end.
    ciphertext = ciphers;
    ciphertext[len] = '\0';
    return ciphertext;
}