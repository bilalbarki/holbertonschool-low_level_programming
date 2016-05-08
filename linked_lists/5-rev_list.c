#include <stdlib.h>
#include "list.h"

/*reverses the order of the nodes 
  in a List*/
void rev_list(List **list){
  List *prev, *current, *next;
  prev=NULL;
  current=*list;
  while (current != NULL)
  {
    next  = current->next;  
    current->next = prev;   
    prev = current;
    current = next;
  }
  *list = prev;
}
