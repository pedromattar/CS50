// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include "dictionary.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}
// Hashes word to a number
unsigned int hash(const char *word)
{
    // provided by: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    unsigned int hash = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        hash = (hash << 2) ^ word[i];
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
int word_sum = 0;
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *file = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        return false;
        return 1;
    }
    word_sum = 0;
    //read strings from file one at a time
    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
            return 1;
        }
        strcpy(n->word, word);// copy the word into a node
        n->next = table[hash(word)];
        table[hash(word)] = n;
        word_sum++;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return word_sum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < 26; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (tmp != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
