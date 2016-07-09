#include "hashtable.h"
#include <stdlib.h>

HashTable *ht_create(unsigned int size) {
  HashTable *newHashTable;
  unsigned int i; /*used for looping*/

  /*allocate memory for a new HashTable*/
  newHashTable = malloc( sizeof (HashTable) );
  if (newHashTable == NULL) {
    return NULL;
  }
  newHashTable->size = size;

  /*create and initialize cells for the new HashTable*/
  newHashTable->array = malloc ( sizeof (List *) * size );
  if (newHashTable->array == NULL) {
    return NULL;
  }
  for (i=0; i < size; i++) {
    newHashTable->array[i] = NULL; /*default value*/
  }
  return newHashTable;
}
