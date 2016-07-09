#include "hashtable.h"
#include <stdlib.h>

/*frees a HashTable*/
void ht_free(HashTable *hashtable) {
  int i;
  for (i = hashtable->size - 1; i >= 0; i--) {
    List *next;
    List *temp = hashtable->array[i];
    for (; temp ; temp = next) { 
      next = temp->next;
      free(temp->key);
      free(temp->value);
      free(temp);
    }
  }
  free(hashtable->array);
  free(hashtable);
}
