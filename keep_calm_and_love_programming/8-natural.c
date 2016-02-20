#include <stdio.h>

int main(void)
{
  int i,sum;
  sum=0;
  /*|| = or*/
  for (i=3;i<1024;i++){
    if (i%3==0 || i%5==0){
      sum=sum+i;
    }
  }
  printf("%d\n",sum);
  return 0;
}
