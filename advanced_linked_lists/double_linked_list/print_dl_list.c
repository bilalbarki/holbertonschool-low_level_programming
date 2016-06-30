#include "list.h"
void print_string(char *str);
int print_char(char c);

/*print function for List*/
void print_dl_list(List *list) {
  for(;list;list=list->next) {
    print_string(list->str);
    print_string("\n\t");
    if (list->prev)
      print_string(list->prev->str);
    else
      print_string("NULL");
    print_string("\n\t");
    if (list->next)
      print_string(list->next->str);
    else
      print_string("NULL");
    print_char('\n');
  }
}
