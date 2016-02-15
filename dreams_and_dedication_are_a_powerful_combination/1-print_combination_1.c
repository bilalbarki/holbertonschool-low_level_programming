#include "my_functions.h"

void print_combination_1(void)
{
  int i;
  print_number(0); /*no comma before this*/
  for (i=1;i<10;i++) /*from 1-9*/
    {
      print_char(',');
      print_char(' ');
      print_number(i);
    }
}
