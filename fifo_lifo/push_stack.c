#include <stdlib.h>
#include <string.h>
#include "stack.h"

int push_stack(Stack **list, char *str) {
  Stack *node;
  node = malloc( sizeof(Stack) );
  if (node == NULL) 
    return 1;
  node->str = strdup(str);
  if (node->str == NULL){
    free(node);
    return 1;
  }
  node->next = (*list);
  *list = node;
  return 0;
}
