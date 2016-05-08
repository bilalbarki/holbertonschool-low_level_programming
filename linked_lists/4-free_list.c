#include <stdlib.h>
#include "list.h"

/*frees a list*/
void free_list(List *list){
  List *temp;
  for (;list;list=temp->next){
    temp=list->next;
    free(list->str);
    free(list);
  }
  free(temp->str);
  free(temp);
}
