#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Gus aka Charles Steyer and I walked through the detailed steps we need to do using pseudocode
//Earlier today, after submitting my PSet, I talked Gus through using strings in conditional
//statements

//give c a hint that I'll define function shift
int shift(char c);

int main(int argc, string argv[])
{
    //check if there are two strings in command line - filename + encryption clue
    if (argc == 2)
    {
        //loop through each character in encryption clue i.e. argv[1]
        for (int location = 0, length = strlen(argv[1]); 
             location < length; location++)
        {
            //check whether encryption clue has alphabetic letters
            if (isalpha(argv[1][location]) == 0)
            {
                //if key has non-alphabetic characters, warn user and abort program
                printf("Usage: ./vigenere keyword\n");
                return 0;
            }
        }
    }
    else
    {
        //if no key was provided, warn user and abort program
        printf("Usage: ./vigenere keyword\n");
        return 0;
    }
    //store encryption key from command line as string in "clue"
    string clue = argv[1];
    for (int letter = 0, cluelen = strlen(clue); letter < cluelen; letter++)
    {
        //c is my intended input for the shift function, i.e., each letter from clue function
        char c = clue[letter];
        //my program works well for single letter clues, e.g., it's accurate if the clue is
        //just "a" or just "b" etc., but if my clue is "abc", it runs three times, once where 
        //it shifts plaintext by 0 aka a, 2nd time to shift plaintext by one letter i.e. b, and
        //the third time to shift letters by two positions i.e. c. It prompts for plaintext 
        //with each run. HELP ME??? PLEASE??? HAHAHAHA
        //now, declare plaintext input for later
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
                printf("%c", (plaintext[character] + shift(c) - 'A') % 26 + 'A');
            }
            if (islower(plaintext[character]))
            {
                //shift lowercase letter by key & avoid non-alphabet characters
                printf("%c", (plaintext[character] + shift(c) - 'a') % 26 + 'a');
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
}   

//define shifting function that will lopp through clue characters
int shift(char c)
{
    if (islower(c))
    {
        //my alphabet and the ASCII alphabet are consistently different by 97 i.e. 'a'
        return c - 'a';
    }
    if (isupper(c))
    {
        return c - 'A'; 
    }
    return 0; 
}
