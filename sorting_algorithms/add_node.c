#include <string.h>
#include "list.h"
#include <stdlib.h>

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
  }
  else {
    List *traverse = *list;
    for (; traverse->next ; traverse = traverse->next);
    traverse->next = node;
  }
  return 0;
}
