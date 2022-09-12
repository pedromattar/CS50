#include <stdio.h>
#include <cs50.h>

int main(void)
{   
    /*ask for the name of the user*/
    string name = get_string("What is your name?\n");
    /*show a message that increments the name*/
    printf("Hello, %s\n", name);
}
