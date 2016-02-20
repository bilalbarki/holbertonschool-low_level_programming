#include "my_functions.h" /*contains prototypes*/

void print_combination_2(void)
{
  int i,j; /*for loops*/
  for (i=0;i<9;i++)
    {
      for (j=i+1;j<10;j++) /*note i+1*/
        {
          print_char(i+48);
          print_char(j+48);
          if (!(i==8 && j==9)) /*,' '*/
            {
              print_char(',');
              print_char(' ');
            }
        }
    }
}
