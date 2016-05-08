#include <stdlib.h>
#include "list.h"

int list_size(List *list){
  int i;
  /*if (list==NULL) return 0;*/
  for (i=0; list; list=list->next) i++;
  return i;
}
