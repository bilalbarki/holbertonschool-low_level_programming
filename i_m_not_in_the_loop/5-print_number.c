#include "my_functions.h" /*contains prototypes*/

void print_number(int n)
{
  if (n<0) /*if neg number make it pos and print '-'*/
  {
      n=n*(-1);
      print_char('-');
  }
  int x=(n%10)+48; /*extract last digit & +48 for equivalent ascii*/
  n=n/10; /*remove last digit, int will discard decimal*/
  if (n!=0)
  {
    print_number(n); /*recursive call used for reversing*/
  }
  print_char(x);
}
