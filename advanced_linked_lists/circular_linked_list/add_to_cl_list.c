#include <string.h>
#include <stdlib.h>
#include "list.h"

/*creates new node at the end of the list*/
int add_end_cl_list(List **list, char *str) {
  List *node;
  node = malloc( sizeof (List) );
  if (node == NULL)
    return 1;
  node->str = strdup(str);
  if ( node -> str == NULL ) {
    free(node);
    return 1;
  }
  if (*list == NULL) { /*if list is empty*/
    *list = node;
    node->next = node;
  }
  else { /*if list is not empty*/
    List *last = *list;
    for (; last->next != *list ; last = last->next);
    last->next = node;
    node->next = *list;
  }
  return 0;
}

/*creates new node at the beginning of the list*/
int add_begin_cl_list(List **list, char *str) {
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
    List *last = *list;
    for (; last->next != *list ; last = last->next);
    last->next = node;
    node->next = *list;
  }
  else {
    node->next = node;
  }
  *list = node;
  return 0;
}
