//load function libraries
#include <cs50.h>
#include <stdio.h>

int main(void)
{   //create height integer and do not assign value
        int height;
    do{
        //prompt to reqest value and assign user input to height
        height = get_int("Height:  ");
    }
    //condition to check is height value provided is between 1 and 8 before action
    while(height > 8 || height < 1);
//loop through row, space, next (line) based on height
for (int row = 1; row <= height; row++)
{ 
    for (int space = 0; space < height-row; space++)
    {
        printf(" ");
    }
    for( int next = 0; next < row; next++)
    {
        printf("#");
    }
    printf("\n");
}
}
