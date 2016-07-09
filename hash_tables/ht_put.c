#include "hashtable.h"
HashTable *ht_create(unsigned int size);
#include <string.h>
#include <stdlib.h>

List *search_key(List *list, const char *key);
int strings_compare(const char *s1, const char *s2);

/*adds an element to the HashTable*/
int ht_put(HashTable *hashtable, const char *key, const char *value) {
  List *node;
  int hashed = hash(key, hashtable->size);
  /*search if the key already exists, if it does, then replace the value*/
  if ( ( node = search_key( hashtable->array[hashed], key ) ) != NULL ) {
    free(node->value); /*free previously allocated space by the value*/
    node->value = strdup(value);
    if (node->value==NULL){
      return 1;
    }
  }
  else { /*else create a new node and link it*/
    node = malloc( sizeof(List) );
    if (node == NULL)
      return 1;
    node->key = strdup(key);
    if (node->key == NULL){
      free(node);
      return 1;
    }
    node->value = strdup(value);
    if (node->value == NULL){
      free(node->key);
      free(node);
      return 1;
    }
    node->next =  hashtable->array[hashed];
    hashtable->array[hashed] = node;
  }
  return 0;
}

/*searches for given key in the List*/
List *search_key(List *list, const char *key) {
  for ( ; list != NULL ; list = list ->next ) {
    if ( strings_compare(key, list->key) == 0 )
      return list;
  }
  return NULL;
}

/*string compare function*/
int strings_compare(const char *s1, const char *s2){
  int i;
  for (i=0;*(s1+i)==*(s2+i);i++){
    if (*(s1+i)=='\0')
      return 0;
  }
  return (*(s1+i)-*(s2+i));
}
