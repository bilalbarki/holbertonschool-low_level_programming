#include <stdlib.h>
#include "list.h"

void print_string(char *str);
int print_char(char c);

/*print function for List*/
void print_dcl_list(List *list) {
  List *iterate = list;
  if ( iterate ) {
    do {
      print_string(iterate->str);
      print_string("\n\t");
      print_string(iterate->prev->str);
      print_string("\n\t");
      print_string(iterate->next->str);
      print_char('\n');
      iterate = iterate->next;
    } while(iterate != list);
  }
}
