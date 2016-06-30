#include <stdlib.h>
#include "list.h"

List *array_to_dcl_list(char **);
void print_dcl_list(List *);
void free_dcl_list(List *list);

int main(__attribute__((unused))int ac, char **av)
{
  List *list;

  list = array_to_dcl_list(av);
  if (list == NULL)
    return (1);
  print_dcl_list(list);
  free_dcl_list(list);
  return (0);
}
