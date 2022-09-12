#include <cs50.h>
#include<stdio.h>


int main(void)
{
    //variables to help solve the algorithm
    int bank = 4;
    char response[3][10] = { "AMEX", "MASTERCARD", "VISA"};
    bool checksum = false;
    int c = 0;
    long ten13 = 10000000000000;//10^13
    long ten14 = 100000000000000;//10^14
    long ten15 = 1000000000000000;//10^15
    long ten12 = 1000000000000;//10^12
    //this was a way that i found because <math.h> wasnt indroduced in the course
    int sum = 0;//used to checksum verification
    long number = get_long ("Number: ");
    //dicover how many characters the number has
    for (long count = 1; (number/count ) > 1; count *= 10)
    {
        c++;
    }
    //checksum test number 1
    if ((c % 10) == 0)
    {
        for (int aux=1; aux <= ( c / 2 ) ; aux++)
        {
            if ((((number % (100) ) / 10) * 2) >= 1)
            {
                sum += (((number % (100)) / 10) * 2) / 10;
                sum += (((number % (100)) / 10) * 2) % 10;
                
            }
            else
            {
                sum += ((number % (100) ) / 10)*2;
            }
            if ((((number % (10) ) / 1) * 2) >= 1)
            {
                sum += (((number % (10))) * 2) / 10;
                sum += (((number % (10))) * 2) % 10;
            }
            else
            {
                sum += ((number % (10) ) / 1)*2;
            }
            number = number/10;
        }//close the for loop
    }
    else
    {
        for (int aux=0; aux <= ( c / 2 ) ; aux++)
        {
            if ((((number % (100) ) / 10) * 2) >= 1)
            {
                sum += (((number % (100)) / 10) * 2) / 10;
                sum += (((number % (100)) / 10) * 2) % 10;
            }
            else
            {
                sum += ((number % (100) ) / 10)*2;
            }
            if ((((number % (10) ) / 1) * 2) >= 1)
            {
                sum += (((number % (10))) * 2) / 10;
                sum += (((number % (10))) * 2) % 10;
            }
            else
            {
                sum += ((number % (10) ) / 1)*2;
            }
            number = number/10;
    }
    //test of card brand
    if ((c == 15) && ((number / (ten13) == 34) || (number / (ten13) == 37)))
    {
        bank = 0;
    }
    else if ((c == 16 && (number / (ten14)) == 51) || (c == 16 && (number / (ten14)) == 52) || (c == 16 && (number / (ten14)) == 53)
     || (c == 16 && (number / (ten14)) == 54) || (c == 16 && (number / (ten14)) == 55))
    {
        bank = 1;
    }
    else if (((c==13) && (((number / ten12) == 4))) || ((c == 16) && ((number / ten15) == 4)))
    {
        bank = 2;
    }
    //print the final result in screen
    if (sum % 10 == 0)
    {
        checksum = true;
    }
    if (checksum == true && bank != 4)
    {
        if (bank == 1)
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("%s\n", response[bank]);
        }
    }
    else
    {
    printf("INVALID\n");
    }
}
}
