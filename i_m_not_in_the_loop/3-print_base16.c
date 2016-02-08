#include "my_functions.h"

void print_base16(void) /*prints all the numbers of base 16*/
{
  for (char x='0';x<='9';x++) /*prints 0-9*/
  {
    print_char(x);
  }

  for (char x='A';x<='F';x++) /*prints A-F*/
  {
    print_char(x);
  }
}
