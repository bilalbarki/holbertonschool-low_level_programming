#include <string.h>
#include <stdlib.h>
#include "list.h"

/*creates new node at the end of the list*/
int add_end_dl_list(List **list, char *str) {
  List *node;
  node = malloc( sizeof (List) );
  if (node == NULL)
    return 1;
  node->str = strdup(str);
  if ( node -> str == NULL ) {
    free(node);
    return 1;
  }
  node->next = NULL;
  if (*list == NULL) {
    *list = node;
    node->prev = NULL;
  }
  else {
    List *traverse = *list;
    for (; traverse->next ; traverse = traverse->next);
    traverse->next = node;
    node->prev = traverse;
  }
  return 0;
}

/*creates new node at the beginning of the list*/
int add_begin_dl_list(List **list, char *str) {
  List *node;
  node = malloc( sizeof (List) );
  if (node == NULL)
    return 1;
  node->str = strdup(str);
  if ( node -> str == NULL ) {
    free(node);
    return 1;
  }
  node->next = *list;
  if ( *list != NULL ) {
    (*list)->prev = node;
  }
  node->prev = NULL;
  *list = node;
  return 0;
}
