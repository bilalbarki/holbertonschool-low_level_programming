#include "hashtable.h"
#include <stdlib.h>

List *find_key(List *list, const char *key);
int ht_put(HashTable *hashtable, const char *key, const char *value);
int str_compare(const char *s1, const char *s2);

/*gets the paired value of a key from the given hashtable*/
char *ht_get(HashTable *hashtable, const char *key) {
  List *node;
  int hashed = hash(key, hashtable->size);
  if ( ( node = find_key( hashtable->array[hashed], key ) ) != NULL ) {
    return node->value;
  }
  else {
    return NULL;
  }
}

/*searches for the key in the given list*/
List *find_key(List *list, const char *key) {
  for ( ; list != NULL ; list = list ->next ) {
    if ( str_compare(key, list->key) == 0 )
      return list;
  }
  return NULL;
}

/*string compare function*/
int str_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}
