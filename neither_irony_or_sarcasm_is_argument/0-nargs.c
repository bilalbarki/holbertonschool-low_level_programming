/*prints number of arguments*/
#include <stdio.h>

int main(int ac, char **av){
  av=av;
  printf("%d\n",ac-1);
  return 0;
}
