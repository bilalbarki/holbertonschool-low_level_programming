#include <stdio.h>
#include <stdlib.h>

int (*get_op_func(char c))(int, int);

int main(int ac, char **av){
  if (ac==4 && get_op_func(*av[2])!=(NULL)){
    printf("%d\n", (*get_op_func(*av[2]))(atoi(av[1]), atoi(av[3])));   
    return 0;
  }
  return 1;
}
