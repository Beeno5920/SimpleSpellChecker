// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // TODO
        node *newWord = malloc(sizeof(node));

        if(newWord == NULL){
            unload();
            return false;
        }

        strcpy(newWord->word, word);

        unsigned int index = hash(word);
        if (hashtable[index] == NULL) {
            hashtable[index] = newWord;
            newWord->next = NULL;
        } else {
            newWord->next = hashtable[index];
            hashtable[index] = newWord;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned int count = 0;

    for (int i = 0; i < N; i++) {
        node *cursor = hashtable[i];
        while (cursor != NULL) {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int index = hash(word);
    node *cursor = hashtable[index];
    char temp[LENGTH + 1];

    for(int i = 0, n = strlen(word); i < n; i++){
        temp[i] = tolower(word[i]);
    }
    temp[strlen(word)] = '\0';

    if(hashtable[index] == NULL)
        return false;

    while(cursor != NULL){

        if(strcmp((cursor->word), temp) == 0)
            return true;

        cursor = cursor->next;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++){

        node *cursor = hashtable[i];
        if(hashtable[i] == NULL)
            continue;

        while(cursor != NULL){
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }

    }

    return true;
}
