#include "my_functions.h" /*contains prototypes*/

/*Prints P for pos int, N for neg, Z for 0*/
void positive_or_not(int n)
{
  if (n>0)
  {
      print_char('P');
  }
  else if (n<0)
  {
      print_char('N');
  }
  else
  {
      print_char('Z');
  }
}
