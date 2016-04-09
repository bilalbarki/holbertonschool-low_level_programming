/*gets the specific function address*/

#include <stdio.h>

int op_add(int a, int b);
int op_sub(int a, int b);
int op_mul(int a, int b);
int op_div(int a, int b);
int op_mod(int a, int b);

int (*get_op_func(char c))(int, int){
  int x;
  char symbols[5] = {'+', '-', '*', '/', '%'};
  int (*ads[5])(int, int) = {&op_add,&op_sub,&op_mul,&op_div,&op_mod};
  for (x=0;x<5;x++) if (c==symbols[x]) return ads[x];
  return NULL;
}
