#include <stdlib.h>
#include "list.h"

/*frees a simple circular list*/
void free_cl_list(List *list) {
  List *temp;
  List *head = list;
  if (list) {
    do {
      temp = list->next;
      free(list->str);
      free(list);
      list = temp;
    } while( list != head );
  }
}
