#include <stdlib.h>
#include "list.h"

/*frees a double linked List*/
void free_list(List *list) {
  List *temp;
  for ( ; list ; list = temp ) {
    temp = list->next;
    free(list->str);
    free(list);
  }
}
