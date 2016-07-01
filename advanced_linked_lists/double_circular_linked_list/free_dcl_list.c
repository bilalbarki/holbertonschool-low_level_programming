#include <stdlib.h>
#include "list.h"

/*frees a double circular list*/
void free_dcl_list(List *list) {
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
