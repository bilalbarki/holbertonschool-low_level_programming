#include <stdlib.h>
#include "tree.h"

void free_children(List *list);

/*frees ntree*/
void ntree_free(NTree *tree) {
  if (tree!=NULL) {
    free(tree->str);
    if (tree->children != NULL)
      free_children(tree->children);
    free(tree);
  }
}

/*frees ntree children*/
void free_children(List *list) {
  List *next;
  next = list;
  while (next) {
    next = list->next;
    ntree_free(list->node);
    free(list);
    list = next;
  }
}
