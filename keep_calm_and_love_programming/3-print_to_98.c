#include <stdio.h>

void print_to_98(int n)
{
  if (n<99){ /*if less than 99*/
    for (;n<99;n++){
      printf("%d",n);
      if (n<98){
	printf(",");
      }
    }
  }
  else{ /*if greater than 99*/
    for (;n>97;n--){
      printf("%d",n);
      if (n>98){
        printf(",");
      }
    }
  }
  printf("\n");
}

