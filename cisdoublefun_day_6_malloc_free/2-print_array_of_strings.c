#include <stdio.h>

void print_array_of_strings(char **w){
  int i;
  i=0;
  while (w[i]){
    printf("%s ",w[i]);
    i++;
  }
  printf("\n");
}
