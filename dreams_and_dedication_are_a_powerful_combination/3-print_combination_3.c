#include "my_functions.h" /*contains prototypes*/

void print_combination_3(void)
{
  int i,j,k; /*for nested loops*/
  for (i=0;i<8;i++) /*main loop*/
    {
      for (j=i+1;j<9;j++)
        {
          for (k=j+1;k<10;k++)
            {
              print_number(i);
              print_number(j);
              print_number(k);
              if (!(i==7 && j==8 && k==9))
                {
                  print_char(',');
                  print_char(' ');
                }
            }
        }
    }
}
