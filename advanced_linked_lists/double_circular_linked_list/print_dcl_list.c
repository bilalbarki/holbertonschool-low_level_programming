#include <stdlib.h>
#include "list.h"

void print_string(char *str);
int print_char(char c);

/*print function for List*/
void print_dcl_list(List *list) {
  List *iterate = list;
  if ( iterate == NULL )
    return;
  do {
    print_string(iterate->str);
    print_string("\n\t");
    if (iterate->prev)
      print_string(iterate->prev->str);
    else
      print_string("NULL");
    print_string("\n\t");
    if (iterate->next)
      print_string(iterate->next->str);
    else
      print_string("NULL");
    print_char('\n');
    iterate=iterate->next;
  } while(iterate != list);
}
