#include <stdlib.h>
#include "list.h"

int print_char(char c);
void print_string(char *str);

/*prints each element of a List*/
void print_list(List *list){
  for(;list;list=list->next){
    print_string(list->str);
    if (list->next){
      print_char(',');
      print_char(' ');
    }
  }
  print_char('\n');
}

/*prints string*/
void print_string(char *str){
  for (;*str;str++) print_char(*str);
}
