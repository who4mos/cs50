// Implements a dictionary's functionality

#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
  char word[LENGTH + 1];
  struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 143091;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
  int idx = hash(word);
  node *aux = table[idx];
  while (aux) {
    if (strcasecmp(aux->word, word) == 0) {
      return true;
    }
    aux = aux->next;
  }
  
  return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
  int n = strlen(word);
  int sum = 0;
  for (int i = 0; i < n; i++) {
    unsigned int c = tolower(word[i]); // get ascii value of current char
    sum += (c+1) * (i + 33); // updates sum using prime
  }

  return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
  // open dict file
  FILE *dictFile = fopen(dictionary, "r");
  if (!dictFile) {
    return false;
  }

  // read each word and add to hash table
  char buf[LENGTH+2]; // LENGTH of word + '\n' + '\0'
  while (fgets(buf, sizeof(buf), dictFile)) {
    int n = strlen(buf);
    if (buf[n - 1] == '\n') {
      buf[n - 1] = '\0';
    }

    node *new = (node *)malloc(sizeof(node));
    if (!new) {
      fclose(dictFile);
      return false;
    }
    
    strcpy(new->word, buf);
    new->next = NULL;

    int idx = hash(new->word);
    new->next = table[idx];
    table[idx] = new;
  }

  fclose(dictFile);
  return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
  int count = 0;
  node *aux;
  for (int i = 0; i < N; i++) {
    aux = table[i];
    while (aux) {
      count++;
      aux = aux->next;
    }
  }
  return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
  for (int i = 0; i < N; i++) {
    node *aux = table[i];

    while (aux) {
      node *tmp = aux;
      aux = aux->next;
      free(tmp);
    }
    free(aux);
  }

  return true;
}
