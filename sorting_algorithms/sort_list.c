#include <stdio.h>
#include "list.h"
int node_cmp(List *node1, List *node2);
void swap(List *a, List *b);

/*sorts a List*/
void sort_list(List **list, int (*cmp_func)(List *, List *)) {
  List *traverse = *list;
  List *yes;
  if (*list == NULL) return;
  for (; traverse!=NULL; traverse=traverse->next) {
    for (yes = *list; yes->next!=NULL; yes=yes->next) {
      if ((*cmp_func)(yes, yes->next) > 0) {
	swap(yes, yes->next);
      }
    }
  }
}

/*swaps str of the node*/
void swap(List *a, List *b)
{
  char *temp = a->str;
  a->str = b->str;
  b->str = temp;
}
