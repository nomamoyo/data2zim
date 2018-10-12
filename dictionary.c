// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "stdlib.h"
#include "string.h"
#include "dictionary.h"

// declare counter to count the number of words in dictionary and set it to zero
int word_counter = 0;

// represents number of buckets in a hash table (corresponds to num letters in alphabet)
#define N 26

// declare index to ID hashtable buckets
int index;

// define a node structure for use in hash table links
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// represents a hash table with N aka 26 buckets
node *hashtable[N];

// hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // buffer for a word
    char word[LENGTH + 1];

    // insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // dynamically allocate space for node
        node *new_node = malloc(sizeof(node));

        // check to make sure I didn’t run out of memory
        if (new_node == NULL)
        {
            return false;
        }

        // copy word from dictionary to new node
        strcpy(new_node->word, word);

        // figure out bucket/index in hashatable, wherein I should store the dictionary word using the hash function
        index = hash(word);

        // make new node next point to the old head
        new_node->next = hashtable[index];

        // make the head point to the new word node - voila - you're now at the top of the linked list!
        hashtable[index] = new_node;

        // add one word to counter
        word_counter++;
    }

    // close dictionary because I've reached the end of the dictionary file
    fclose(file);

    // return true to indicate success because load is a boolean variable
    return true;
}

// returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // give me number of words in dictionary - been counting while loading
    return word_counter++;
}

// returns true if word is in dictionary else false
bool check(const char *word)
{
    // since dictionary only has lower case words, I need to convert all input text words to lowercase
    // declare lowercase word "input_word" to store all the words from the text
    char input_word[LENGTH + 1];

    // loop to iterate over letters and convert all input text words to lowercase
    for (int i = 0; i < strlen(word); i++)
    {
        // if letter is uppercase change it to lowercase
        if (isupper(word[i]))
        {
            input_word[i] = tolower(word[i]);
        }
        // but if it's already lowercase just keep it as is
        else
        {
            input_word[i] = word[i];
        }
    }

    // append marker (null "\0") to signal the end of an input_word before checking if it's in the dictionary
    input_word[strlen(word)] = '\0';

    // use hash to locate the reference bucket for word comparison and return the index
    index = hash(input_word);

    // declare a cursor and set it to the beginning of the appropriate linked list in the hash table
    node *cursor = hashtable[index];

    // iterate through linked list until you get to the end where the cursor = NULL
    while (cursor != NULL)
    {
        // compare input_word to dictionary word that the cursor is pointing to
        if (strcmp(input_word, cursor->word) == 0)
        {
            // if the word is in the dictionary return true
            return true;
        }
        // otherwise keep going down the linked list nodes checking
        cursor = cursor->next;
    }
    return false;
}

// unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // free memory throughout hashtable buckets
    for (int i = 0; i > N; i++)
    {
        //declare node cursor to go through hashtable
        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            // create a temporary node to store the cursor
            node *temp = cursor;

            // move actual cursor to teh next node before freeing temp node
            cursor = cursor->next;

            // free temp node
            free(temp);
        }

        // trying to free more nodes to get rid of valgrind issue abotu reachable bytes (not working)
        free(cursor);
    }
    return true;
}
