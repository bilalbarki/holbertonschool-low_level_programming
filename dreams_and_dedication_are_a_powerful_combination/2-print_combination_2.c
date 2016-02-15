#include "my_functions.h"

void print_combination_2(void)
{
  int i,j;
  for (i=0;i<9;i++)
    {
      for (j=i+1;j<10;j++)
        {
          print_number(i);
          print_number(j);
          if (!(i==8 && j==9))
            {
              print_char(',');
              print_char(' ');
            }
        }
    }
}
