#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>


int main(int argc, string argv[])
{
    string caps = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string low = "abcdefghijklmnopqrstuvwxyz";
    bool repeat = false;


    if (argc == 2)
    {
        if (strlen(argv[1]) != 26)//when the lenght is not 26
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        // if everything is okay
        for (int i = 0; i < strlen(argv[1]); i++) // percorre todo o texto argv
        {
            if (((int) argv[1][i] >= 65 && (int) argv[1][i] <= 90) || ((int) argv[1][i] >= 97
                    && (int) argv[1][i] <= 122))//test if theres only letters in the argv[1]
            {

            }
            else//when the arg is not okay
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }

        //duplicate characters

            if (repeat == true)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
        string plaintext = get_string("Plaintext: ");


        int sum;//when the input is valid
        for (int aux = 0; aux < strlen(plaintext); aux++)//percorre todo o plaintext
        {
            if (plaintext[aux] >= 'a' && plaintext[aux] <= 'z')//when the character is "LOWER"
            {
                sum = 0;
                while (plaintext[aux] != low[sum])
                {
                    sum++;

                }
                if (argv[1][sum] <= 'a')
                {
                    plaintext[aux] = (char)(argv[1][sum]) + 32;
                }
                else
                {
                    plaintext[aux] = (char) argv[1][sum];
                }
            }
            else if (plaintext[aux] >= 'A' && plaintext[aux] <= 'Z')
            {
                sum = 0;
                while (plaintext[aux] != caps[sum])
                {
                    sum++;
                }
                if (argv[1][sum] >= 'a')//when the arg is in lower
                {
                    plaintext[aux] = (char) argv[1][sum] - 32;
                }
                else
                {
                    plaintext[aux] = (char) argv[1][sum];
                }
            }
        }

        printf("ciphertext: %s\n", plaintext);
        return 0;

    }
    else // works well
    {
        printf("Usage: ./substitution key\n");// works well
        return 1;
    }
}
