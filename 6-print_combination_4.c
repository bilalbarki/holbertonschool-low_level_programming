#include "my_functions.h"

void print_combination_4(void)
{
  int i,j;
  for (i=0;i<100;i++)
    {
      for (j=i+1;j<100;j++) /*start 1 after i*/
        {
          if (i<10){  /*append 0 with <10 */
            print_number(0);
          }
          print_number(i);
          print_char(' ');
          if (j<10){   /*append 0 with <10 */
            print_number(0);
          }
          print_number(j);
          if (!(i==98 && j==99))  /*,' '*/
            {
              print_char(',');
              print_char(' ');
            }
        }
    }
}
