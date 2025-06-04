// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 113759;

// Hash table
node *table[N];
unsigned int index_bucket;
unsigned int word_counter;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    index_bucket = hash(word);
    node *current = table[index_bucket];

    while (current != NULL)
    {
        if (strcasecmp(word, current->word) == 0)
        {
            return true;
        }
        current = current->next; // Move to the next node in the list
    }

    return false; // Word not found
}

// Hashes word to a number (the words will be passed one by one, implemented in speller file)
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]))
        {
            total += toupper(word[i]) - 'A';
        }
    }

    return total % N;
}

// Loads dictionary into memory (each word!), returning true if successful, else false
bool load(const char *dictionary)
{
    // first open the file and read it
    FILE *file = fopen(dictionary, "r");
    // handling null case
    if (file == NULL)
    {
        return false;
    }

    // word variable of length priorly determined + the null terminator
    char word[LENGTH + 1];

    // with scanf im scanning the opened file and allocating memory to it like so: (EOF means "end
    // of file")
    while (fscanf(file, "%s", word) != EOF)
    {
        // im creating a new node each time that serves as my vehicule to allocate size to the found
        // word in the file (each string)
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            fclose(file);
            return false;
        }

        // then im copying my word to the node, and for the "next" part of the node, i have to find
        // its place in the hash table (priorly define as node*table[size of the alphabet = 26]),

        strcpy(n->word, word);

        // the bucket number where this letter in the alphabet is going to go is being given by the
        // has function, based on its first letter, and it then serves as the index
        index_bucket = hash(word);

        // now the word will be at the head of the list, meaning the word has now a pointer to the
        // next word in the index (the prior head), and the index is now the newly appended word
        n->next = table[index_bucket];
        table[index_bucket] = n;
        word_counter++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_counter > 0)
    {
        return word_counter;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // we iterate through the hash table, and we have to free not only the first node that matches
    // the index head, but all of the possible linked list after it
    for (int i = 0; i < N; i++)
    {
        // we stablish the vehiculo for the head node
        node *current = table[i];

        // while it exists, we will use a temporary variable to store the next value and free the
        // first one, but without losing the link to the next
        while (current != NULL)
        {
            node *tmp = current->next;
            free(current);
            current = tmp;
        }
    }

    return true;
}
