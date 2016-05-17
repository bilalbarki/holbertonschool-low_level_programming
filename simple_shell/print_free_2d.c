#include <stdlib.h>
#include "functions.h"

/*prints the output two dimentional array*/
void print_tab(char **split){
  int i;
  for (i=0;split[i];i++){
    print_line(split[i]);
    print_char('\n');
  }
}

/*frees space*/
void free_tab(char **split){
  int i;
  for (i=0;split[i];i++){
    free(split[i]);
  }
  free(split[i]);
  free(split);
}
