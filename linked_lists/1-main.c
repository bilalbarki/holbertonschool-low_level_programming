#include <stdlib.h>
#include "list.h"

List *params_to_list(int ac, char **av);

int main(int ac, char **av)
{
  List *params_list;

  params_list = params_to_list(ac, av);
  if (params_list == NULL)
    return (1);
  return (0);
}
