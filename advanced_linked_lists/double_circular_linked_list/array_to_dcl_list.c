#include "list.h"
#include <stdlib.h>
int add_end_dcl_list(List **, char *);

/*converts an array to double circular List*/
List *array_to_dcl_list(char **array) {
  List *list;
  int i;
  list = NULL;
  for (i=0 ; array[i] ; i++) {
    add_end_dcl_list(&list, array[i]);
  }
  return list;
}
