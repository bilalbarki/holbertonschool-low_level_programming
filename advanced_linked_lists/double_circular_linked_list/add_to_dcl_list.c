#include <string.h>
#include <stdlib.h>
#include "list.h"

/*creates new node at the end of the double circular List*/
int add_end_dcl_list(List **list, char *str) {
  List *node;
  node = malloc( sizeof (List) );
  if (node == NULL)
    return 1;
  node->str = strdup(str);
  if ( node -> str == NULL ) {
    free(node);
    return 1;
  }
  if (*list == NULL) {
    *list = node;
    node->prev = node;
    node->next = node;
  }
  else {
    List *last = (*list)->prev;
    (*list)->prev = node;
    last->next = node;
    node->prev = last;
    node->next = *list;
  }
  return 0;
}

/*creates new node at the beginning of the double circular list*/
int add_begin_dcl_list(List **list, char *str) {
  List *node;
  node = malloc( sizeof (List) );
  if (node == NULL)
    return 1;
  node->str = strdup(str);
  if ( node -> str == NULL ) {
    free(node);
    return 1;
  }
  if ( *list != NULL ) {
    node->prev = (*list)->prev;
    (*list)->prev->next = node;
    (*list)->prev = node;
    node->next = *list;
  }
  else {
    node->prev = node;
    node->next = node;
  }
  *list = node;
  return 0;
}
