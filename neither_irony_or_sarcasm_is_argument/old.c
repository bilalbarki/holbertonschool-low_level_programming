#include <stdio.h>

int main(int ac, char **av){
  int i, flag;
  for( i=1, flag=0; i<ac ; i++ ){
    if (*av[i]=='-' && *(av[i]+1)=='-' && *(av[i]+2)!='\0'){
       printf("%s", av[i]+2);
       printf(", ");
       flag=1;
     }
    else if (*av[i]=='-' && *(av[i]+1)!='\0' && flag==0){
       printf("%s", av[i]+1);
       printf(", ");
     }
  }
  printf("\n");
  return 0;
}
