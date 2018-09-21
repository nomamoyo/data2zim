#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{   
    float change;                               //declare float variable for change                            
    do{ 
       change = get_float("Change owed: \n");   //prompt user for change
    }
    while(change < 0.009);                      //keep prompting user until they provide positive value, at least 1 cent
    int cents = round(change * 100);            //convert change into cents as integer
    int remainder = cents;                      //remainder will be the remaining change after giving out each coin
    int coins;                                  //coins is the number of coins - will accumulate over each while loop
    while (remainder >= 25){                    //repeat until max number of quarters are given
        coins = coins + 1;                      //increase coins count by 1
        remainder = remainder - 25;             //calculate remaining change
    }
    while(remainder >= 10){                     //repeat until max number of dimes are given
        coins = coins + 1;
        remainder = remainder - 10;
    }
    while(remainder >= 5){                      //repeat until max number of nickels are given
        coins = coins + 1;
        remainder = remainder - 5;
    }
    while(remainder >= 1){                      //repeat until max number of pennies are given
        coins = coins + 1;
        remainder = remainder - 1;
    }
    printf("I have %i coin(s).\n", coins);      //print number of coins given back
}

