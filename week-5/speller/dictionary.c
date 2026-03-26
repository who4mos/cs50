// Implements a dictionary's functionality

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <strings.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node {
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 42069;

int loaded = 0;
    
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word) {
    int id = hash(word);

    for (node *aux = table[id]; aux != NULL; aux = aux->next) {
        if (strcasecmp(word, aux->word) == 0) {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) {
    int sum = 42069;

    for (int i = 0; word[i] != '\0'; i++) {
        sum += toupper(word[i]) + sum * 33;
    }
    
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary) {
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        return false;
    }

    for (int i = 0; i < N; i++) {
        table[i] = NULL;
    }
    
    char c, word[LENGTH];
    int i = 0;
    while (fread(&c, sizeof(char), 1, dict)) {
        if (c == '\n') {
            // terminate word
            word[i] = '\0';

            // create new node
            int id = hash(word);
            node *new = (node *) malloc(sizeof(node));
            if (new == NULL) {
                fclose(dict);
                return false;
            }
            
            strcpy(new->word, word);
            new->next = table[id];
            table[id] = new;

            loaded++;
            
            // reset to next word
            i = 0;
            continue;
        }
        word[i] = c;
        i++;
    }
    
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void) {
    return loaded;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void) {

    for (int i = 0; i < N; i++) {
        node *aux = table[i];
        while (aux != NULL) {
            node *next = aux->next;
            free(aux);
            aux = next;
        }

    }
    return true;
}
