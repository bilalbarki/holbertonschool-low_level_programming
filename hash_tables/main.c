#include "hashtable.h"
#include <stdlib.h>
HashTable *ht_create(unsigned int size);
int ht_put(HashTable *hashtable, const char *key, const char *value);
void ht_free(HashTable *hashtable);
char *ht_get(HashTable *hashtable, const char *key);

#include <stdio.h>

int main() {
  HashTable *newHashTable;
  if ( (newHashTable = ht_create(10)) == NULL )
    return 1;
  
  if ( (ht_put(newHashTable, "key1", "value1") ) == 1 )
    return 1;
  if ( (ht_put(newHashTable, "key1", "value1 changed") ) == 1 )
    return 1;
  if ( (ht_put(newHashTable, "key2", "value2") ) == 1 )
    return 1;
  if ( (ht_put(newHashTable, "key3", "value3") ) == 1 )
    return 1;
  printf("%s\n", ht_get(newHashTable, "key1") );
  printf("%s\n", ht_get(newHashTable, "key2") );
  printf("%s\n", ht_get(newHashTable, "key3") );
  if ( (ht_put(newHashTable, "key2", "value2 changed") ) == 1 )
    return 1;
  printf("%s\n", ht_get(newHashTable, "key2") );
  ht_free(newHashTable);
  return 0;
}
