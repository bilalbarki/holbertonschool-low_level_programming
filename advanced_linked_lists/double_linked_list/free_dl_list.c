#include <stdlib.h>
#include "list.h"

/*frees a list*/
void free_dl_list(List *list) {
  List *temp;
  for ( ; list ; list = temp ) {
    temp = list->next;
    free(list->str);
    free(list);
  }
}
