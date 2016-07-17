#include "list.h"
#include <stdlib.h>
int add_end_dl_list(List **, char *);

/*converts an array to double linked list*/
List *array_to_list(char **array) {
  List *list;
  int i;
  list = NULL;
  for (i=0 ; array[i] ; i++) {
    if ( (add_end_dl_list(&list, array[i] )) == 1 ) {
      return NULL;
    }
  }
  return list;
}
