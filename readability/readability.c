#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    //declartion of variables
    float s;
    float l;
    float index;
    int sentences = 0;
    int word = 1;
    int letter = 0;

    string text = get_string("Text: "); // ask for a text from the user 
    int n = strlen(text);// check the number of characters the text has
    for (int i = 0; i < n; i++)//for each character in the text
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letter ++;
        }
        else if (text[i] == ' ' && text[(i - 1)] == ' ')
        {
            letter --;
        }
        else if (text[i] == ' ')
        {
            word ++;
        }
        else if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            sentences ++;
        }
        
    }
    float la = (letter * 100) / word;//calculates the averege quantity of letters per 100 words
    float sa = (sentences * 100) / word;

    float in = 0.0588 * la - 0.296 * sa - 15.8;
    //if (in > 7.5 && in < 7.6)
    //{
    //    in = 7;
    //    printf("Grade %.0f\n", round(in));
    //}
    //else
    if (round(in) >= 1 && round(in) < 16)
    {
        printf("Grade %.0f\n", (in));
    }
    else if (round(in) < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
    //printf("letters: %i \n", letter);
    //printf("words: %i \n", word);
    //printf("sentences: %i \n", sentences);
}
