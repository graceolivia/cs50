// Implements a dictionary's functionality
// Hash Function Credit to  Neel Mehta at:
// https://github.com/hathix/cs50-section/blob/master/code/7/sample-hash-functions/good-hash-function.c

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// Number of buckets in hash table
const unsigned int N = 150000;

//total number of words
unsigned long wordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashNumber = hash(word);
    node *currentNode = table[hashNumber];
    //if nothing in node, return false
    if (currentNode == NULL)
    {
        return false;
    }
    //check if it matches the first in node
    if (strcasecmp(word, currentNode->word) == 0)
    {
        return true;
    }
    //while loop to go through linked list
    else 
        while (currentNode->next != NULL)
        {
            currentNode = currentNode->next;
            if (strcasecmp(word, currentNode->word) == 0)
            {
                return true;
            }
        }

    return false;
}

// Hashes word to a number
// Hash credit to Neel Mehta (link at top of document)
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    
    for (const char *ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }
    return hash % N;
 

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;

    }

    //word array to store words in
    char buffer[46];

    //set to all zeros
    memset(buffer, 0, 46);
    //read with fscanf
    while (fscanf(file, "%s", buffer) != EOF)
    {
        //temporary hash value holder
        unsigned long tempHashValue = 0;
        //create new node using malloc
        node *newNode = malloc(sizeof(node));
        if (newNode != NULL)
        {
            strcpy(newNode->word, buffer);
            tempHashValue = hash(newNode->word);
            
            //check if spot in hash table is filled. if not... set pointer to NULL
            if (table[tempHashValue] == 0)
            {
                newNode->next = NULL;
            }
            //if first spot is filled, set pointer of new node to old
            else
            {
                newNode->next = table[tempHashValue];
            }
            //return false if not successfully loaded
            if (strcmp(newNode->word, buffer) != 0)
            {
                printf("word could not be loaded.\n");
                return false;
            }

            //use hash to put word into hash-generated spot at linked list
            table[tempHashValue] = newNode;
            //increase word counter
            wordCounter++;
        }

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCounter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        free(cursor);

    }
    return true;
}



