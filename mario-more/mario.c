#include <cs50.h>
#include<stdio.h>
int main(void)
{
    int height = -1;
    while (height > 8 || height < 1)
    {
        height = get_int("Height: ");
    }//this while loop will verify the user input, to make sure the number is between 1 and 8
    for (int counter = 0; counter < height; counter++)
    {
        for (int printed = 0; printed < (height - counter - 1); printed++) //print spaces before the #
        {
            printf(" ");
        } //print the spaces before #
        for (int printed = 0; printed <= counter ; printed++) //print the #
        {
            printf("#");    
        }
        printf("  ");
        for (int printed = 0; printed <= counter; printed++)
        {
            printf("#");    
        }
        printf("\n");
    }//close first for (the counter one)
}//close main(void)

