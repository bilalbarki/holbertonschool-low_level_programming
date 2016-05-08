#include <stdlib.h>
#include "list.h"

/*returns the number of nodes in a list*/
int list_size(List *list){
  int i;
  for (i=0; list; list=list->next) i++;
  return i;
}
