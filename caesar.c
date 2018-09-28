#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //check if there are two strings - filename + key
    if (argc == 2)
    {
        for (int location = 0, length = strlen(argv[1]); 
             location < length; location++)
        {
            //check if key has non-digits
            if (isdigit(argv[1][location]) == 0)
            {
                //if key is wrong format, warn user and abort program
                printf("Usage: ./caesar key\n");
                return 0;
            }
        }
    }
    else
    {
        //if no key was provided, warn user and abort program
        printf("Usage: ./caesar key\n");
        return 0;
    }
    //store encryption key from command line as integer in "shiftkey"
    int shiftkey = atoi(argv[1]);
    //declare plaintext input
    string plaintext;
    //prompt user for input and store in "plaintext"
    plaintext = get_string("plaintext: ");
    //print the beginning part of output
    printf("ciphertext: ");
    //iterate character by character through plaintext input
    for (int character = 0, len = strlen(plaintext); character < len; character++)
    {
        if (isupper(plaintext[character]))
        {
            //shift uppercase letter by key & avoid non-alphabet characters
            printf("%c", (plaintext[character] + shiftkey - 'A') % 26 + 'A');
        }
        if (islower(plaintext[character]))
        {
            //shift lowercase letter by key & avoid non-alphabet characters
            printf("%c", (plaintext[character] + shiftkey - 'a') % 26 + 'a');
        }
        //check if input plaintext has spaces or punctuation marks
        if (isspace(plaintext[character]) || ispunct(plaintext[character]))
        {
            //if there are spaces or punctuation marks, preserve them output
            printf("%c", plaintext[character]); 
        }    
    }
    printf("\n");
}
