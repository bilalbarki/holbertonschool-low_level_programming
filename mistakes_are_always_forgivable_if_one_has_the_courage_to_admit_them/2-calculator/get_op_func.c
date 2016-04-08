#include <stdio.h>

int op_add(int a, int b);
int op_sub(int a, int b);
int op_mul(int a, int b);
int op_div(int a, int b);
int op_mod(int a, int b);

int (*get_op_func(char c))(int, int){
  int x;
  int (*ads[5])(int, int) = {&op_add,&op_sub,&op_mul,&op_div,&op_mod};
  x = (c == '+')*1+(c == '-')*2+(c == '*')*3+(c == '/')*4+(c == '%')*5 - 1;
  if (x == -1)
    return NULL;
  return (ads[x]);
}
